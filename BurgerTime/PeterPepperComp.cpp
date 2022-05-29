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
	int deviation = 5;
	for (int levelHeight : m_LevelHeights)
	{
		if (abs(levelHeight - m_pGameObject->GetWorldPosition().y) <= deviation)
		{
			m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, levelHeight);
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

}

void PeterPepperComp::TryClimb(int direction)
{
	if(CanClimbDown() && direction == -1 || CanClimbUp() && direction == 1)
	{
		auto pos = m_pGameObject->GetPosition();
		m_pGameObject->SetPosition(pos.x, pos.y + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction);
	}
}

void PeterPepperComp::StartRunAnim(int direction)
{
	if (!IsOnFloor()) return;
	auto text = m_pGameObject->GetComponent<dae::TextureComponent>();
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	anim->SetCurrentAnimation("run");
	text->m_Flipped = direction == 1;
}

void PeterPepperComp::Run(int direction)
{
	if (!IsOnFloor()) return;
	if (direction == 1 && !CanMoveRight()) return;
	if (direction == -1 && !CanMoveLeft()) return;
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction, pos.y);
}

void PeterPepperComp::Update()
{


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
		m_IsTouchingLadder = true;
	}
	if (other->GetComponent<LadderTop>())
	{
		int deviation = 5;
		if(abs(other->GetPosition().y - m_pGameObject->GetPosition().y <= deviation))
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

void PeterPepperComp::AddLevelHeight(int newHeight)
{
	m_LevelHeights.push_back(newHeight);
}

