#include "MiniginPCH.h"
#include "PeterPepperComp.h"

#include "GameObject.h"
#include "GlobalTime.h"
#include "InputManager.h"
#include "PlayerObserver.h"
#include "TextureComponent.h"
#include <AnimationComponent.h>

#include "BlockComp.h"
#include "LadderComp.h"
#include "LadderTop.h"

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
}

void PeterPepperComp::OnDeath()
{
	if (m_LivesLeft > 0) 
		--m_LivesLeft;
	
	std::cout << "PlayerDied, lives left: " << m_LivesLeft << "\n";
	NotifyAllObservers(*m_pGameObject, eEvent::PepperDied);
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
		m_pGameObject->SetPosition(pos.x, pos.y + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction);
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
			m_IsTouchingLadder = true;
	}
	if (other->GetComponent<LadderTop>())
	{
		int deviation = 5;
		if(abs(other->GetWorldPosition().x - m_pGameObject->GetWorldPosition().x) <= deviation)
		{
			m_IsTouchingTopLadder = true;
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

