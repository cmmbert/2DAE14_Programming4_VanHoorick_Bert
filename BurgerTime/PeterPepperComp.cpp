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
#include "EnemyCollision.h"
#include "EnemyManager.h"
#include "GameManager.h"
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
	auto texture = std::make_shared<dae::TextureComponent>(salt.get(), "Burgertime/spritesheet.png", glm::vec4{ 187,16,16,16 });
	salt->AddComponent(texture);
	auto anim = std::make_shared<AnimationComponent>(salt.get(), texture, 0.2f);
	salt->AddComponent(anim);
	anim->AddAnimationFrame("spray", { 187,16 });
	anim->AddAnimationFrame("spray", { 203,16 });
	anim->AddAnimationFrame("spray", { 219,16 });
	anim->AddAnimationFrame("spray", { 235,16 });

	anim->AddAnimationFrame("sprayDown", { 187,32 });
	anim->AddAnimationFrame("sprayDown", { 203,32 });
	anim->AddAnimationFrame("sprayDown", { 219,32 });
	anim->AddAnimationFrame("sprayDown", { 235,32 });

	anim->AddAnimationFrame("sprayUp", { 187,48 });
	anim->AddAnimationFrame("sprayUp", { 203,48 });
	anim->AddAnimationFrame("sprayUp", { 219,48 });
	anim->AddAnimationFrame("sprayUp", { 235,48 });
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
	m_IsDead = true;
	std::cout << "PlayerDied, lives left: " << m_LivesLeft << "\n";
	NotifyAllObservers(*m_pGameObject, eEvent::PepperDied);
	GameManager::GetInstance().PlayerDied();
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	anim->SetCurrentAnimation("death");
	anim->ContinueAnimation();
	m_TimeSincePlayerDied = 0;
}

void PeterPepperComp::ThrowSalt()
{
	if (m_IsDead) return;
	if (m_SaltsLeft == 0) return;
		--m_SaltsLeft;
	m_SaltGo->GetComponent<SaltComp>()->Reset();
	m_pGameObject->GetComponent<AnimationComponent>()->Reset();
	auto anim = m_SaltGo->GetComponent<AnimationComponent>();
	auto texture = m_SaltGo->GetComponent<dae::TextureComponent>();
	texture->m_Flipped = false;
	anim->SetCurrentAnimation("spray");


	auto posOffset = glm::ivec2{ 16 * LevelSettings::Scale,16 * LevelSettings::Scale };
	posOffset *= m_LastDir;
	posOffset.x += m_pGameObject->GetPosition().x;
	posOffset.y += m_pGameObject->GetPosition().y;
	m_SaltGo->SetPosition(posOffset);
	if(m_LastDir == glm::ivec2{ -1,0 })
	{
		anim->SetCurrentAnimation("spray");
		texture->m_Flipped = true;
	}
	else if(m_LastDir == glm::ivec2{ 0,-1 })
	{
		anim->SetCurrentAnimation("sprayDown");
	}
	else if (m_LastDir == glm::ivec2{ 0,1 })
	{
		anim->SetCurrentAnimation("sprayUp");
	}

}

void PeterPepperComp::StartClimbAnim(int direction)
{
	if (m_IsDead || m_IsDisabled) return;
	if (!CanClimbUp() && !CanClimbDown()) return;
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	if(direction == 1)
		anim->SetCurrentAnimation("climbup");
	else
		anim->SetCurrentAnimation("climbdown");
	m_LastDir = { 0, direction };

}

void PeterPepperComp::TryClimb(int direction)
{
	if (m_IsDead || m_IsDisabled) return;
	if(CanClimbDown() && direction == -1 || CanClimbUp() && direction == 1 && m_LastDir == glm::ivec2{0, direction} )
	{
		m_HasRecievedInputThisFrame = true;
		auto pos = m_pGameObject->GetPosition();
		m_pGameObject->SetPosition(m_CurrentLadderXPos, pos.y + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction);
	}
}

void PeterPepperComp::StartRunAnim(int direction)
{
	if (!IsOnFloor() || m_IsDead || m_IsDisabled) return;
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	anim->SetCurrentAnimation("run");
	auto text = m_pGameObject->GetComponent<dae::TextureComponent>();
	text->m_Flipped = direction == 1;
	m_LastDir = { direction, 0 };
}

void PeterPepperComp::TryRun(int direction)
{
	if (!IsOnFloor() || m_LastDir != glm::ivec2{ direction, 0 } || m_IsDead || m_IsDisabled) return;
	m_HasRecievedInputThisFrame = true;
	if (direction == 1 && !CanMoveRight()) return;
	if (direction == -1 && !CanMoveLeft()) return;
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction, pos.y);
	
}

void PeterPepperComp::Update()
{
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	if(!m_IsDisabled)
	{
		if(!m_IsDead)
			m_HasRecievedInputThisFrame ? anim->ContinueAnimation() : anim->StopAnimation();
		else
		{
			m_TimeSincePlayerDied += GlobalTime::GetInstance().GetElapsed();
			if(m_TimeSincePlayerDied > m_TimeBeforeRespawn)
			{
				if (m_LivesLeft > 0)
				{
					--m_LivesLeft;
					GameManager::GetInstance().Reset();
				}
				else
				{
					GameManager::GetInstance().GameOver();
				}
			}
		}
	}
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
	if(auto enemy = other->GetComponent<EnemyCollision>())
	{
		if(!m_IsDead && !enemy->IsSalted())
		{
			auto pos = m_pGameObject->GetPosition();
			auto otherPos = other->GetPosition();
			auto deviation = 24;
			auto distance = sqrt(pow(otherPos.x - pos.x, 2) + pow(otherPos.y - pos.y, 2));
			if (distance < deviation)
				OnDeath();
		}
	}
}

void PeterPepperComp::Reset()
{
	m_IsDead = false;
}

