#include "MiniginPCH.h"
#include "PeterPepperComp.h"

#include "GameObject.h"
#include "GlobalTime.h"
#include "InputManager.h"
#include "PlayerObserver.h"
#include "TextureComponent.h"
#include <AnimationComponent.h>

#include "BlockComp.h"
#include "BoxColliderComp.h"
#include "LadderComp.h"
#include "LadderTop.h"
#include "SaltComp.h"

bool PeterPepperComp::IsOnFloor()
{
	int deviation = 10;
	for (int levelHeight : LevelSettings::m_LevelHeights)
	{
		if (abs(levelHeight - m_pGameObject->GetWorldPosition().y) <= deviation)
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, (float)levelHeight);
			return true;
		}
	}
	return false;
}

PeterPepperComp::PeterPepperComp(dae::GameObject* gameObject) : BaseComponent(gameObject)
{
	//AddObserver(PlayerObserver());
	auto salt = std::make_shared<dae::GameObject>();
	salt->SetSize(16 * LevelSettings::Scale, 16 * LevelSettings::Scale);
	salt->SetPosition({-1000,-1000});
	auto texture = std::make_shared<dae::TextureComponent>(salt.get(), "Burgertime/spritesheet.png", glm::vec4{ 187,17,16,16 });
	salt->AddComponent(texture);
	auto anim = std::make_shared<AnimationComponent>(salt.get(), texture, 0.2f);
	salt->AddComponent(anim);
	anim->AddAnimationFrame("spray", { 187,17 });
	anim->AddAnimationFrame("spray", { 203,17 });
	anim->AddAnimationFrame("spray", { 219,17 });
	anim->AddAnimationFrame("spray", { 235,17 });
	anim->SetCurrentAnimation("spray");
	auto& scene = dae::SceneManager::GetInstance().GetCurrentScene();
	auto saltComp = std::make_shared<SaltComp>(salt.get(), scene);
	salt->AddComponent(saltComp);
	auto coll = std::make_shared<BoxColliderComp>(salt.get(), "salt");
	salt->AddComponent(coll);
	scene.Add(salt);
	m_SaltGo = salt;
}

void PeterPepperComp::OnDeath()
{
	if (m_LivesLeft > 0) 
		--m_LivesLeft;
	
	std::cout << "PlayerDied, lives left: " << m_LivesLeft << "\n";
	NotifyAllObservers(*m_pGameObject, eEvent::PepperDied);
}

void PeterPepperComp::ThrowSalt()
{
	auto pos = glm::ivec2{ 16* LevelSettings::Scale,0 };
	pos.x += m_pGameObject->GetPosition().x;
	pos.y += m_pGameObject->GetPosition().y;
	m_SaltGo->SetPosition(pos);
	m_SaltGo->GetComponent<SaltComp>()->Reset();
	m_pGameObject->GetComponent<AnimationComponent>()->Reset();
}

void PeterPepperComp::StartClimbAnim(int direction)
{
	if (!CanClimbUp() && !CanClimbDown()) return;
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	if(direction == 1)
		anim->SetCurrentAnimation("climbup");
	else
		anim->SetCurrentAnimation("climbdown");

}

void PeterPepperComp::TryClimb(int direction)
{
	if(CanClimbDown() && direction == -1 || CanClimbUp() && direction == 1)
	{
		m_HasRecievedInputThisFrame = true;
		auto pos = m_pGameObject->GetPosition();
		m_pGameObject->SetPosition(m_CurrentLadderXPos, pos.y + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction);
	}
}

void PeterPepperComp::StartRunAnim(int direction)
{
	if (!IsOnFloor()) return;
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	anim->SetCurrentAnimation("run");
	auto text = m_pGameObject->GetComponent<dae::TextureComponent>();
	text->m_Flipped = direction == 1;
}

void PeterPepperComp::TryRun(int direction)
{
	if (!IsOnFloor()) return;
	m_HasRecievedInputThisFrame = true;
	if (direction == 1 && !CanMoveRight()) return;
	if (direction == -1 && !CanMoveLeft()) return;
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction, pos.y);
	
}

void PeterPepperComp::Update()
{
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();

	m_HasRecievedInputThisFrame ? anim->ContinueAnimation() : anim->StopAnimation();
	m_HasRecievedInputThisFrame = false;
	m_IsTouchingLadder = false;
	m_IsTouchingTopLadder = false;
	m_IsTouchingBlock = false;
	m_IsTouchingLeftBlock = false;
	m_IsTouchingRightBlock = false;
}

void PeterPepperComp::OnCollision(dae::GameObject* other)
{
	if (other->GetComponent<LadderComp>())
	{
		int deviation = 5;
		if (abs(other->GetWorldPosition().x - m_pGameObject->GetWorldPosition().x) <= deviation)
		{
			m_IsTouchingLadder = true;
			m_CurrentLadderXPos = other->GetWorldPosition().x;
		}
	}
	if (other->GetComponent<LadderTop>())
	{
		int deviation = 5;
		if(abs(other->GetWorldPosition().x - m_pGameObject->GetWorldPosition().x) <= deviation)
		{
			m_IsTouchingTopLadder = true;
			m_CurrentLadderXPos = other->GetWorldPosition().x;
		}
	}
	if (auto block = other->GetComponent<BlockComp>())
	{
		/*if(block->IsBlockingDirection(Direction::Up)) //Not needed for this game
			m_IsTouchingBlock = true;*/
		if(block->IsBlockingDirection(Direction::Down))
			m_IsTouchingBlock = true;
		if(block->IsBlockingDirection(Direction::Right))
			m_IsTouchingRightBlock = true;
		if(block->IsBlockingDirection(Direction::Left))
			m_IsTouchingLeftBlock = true;
	}
}

