#include "MiniginPCH.h"
#include "PeterPepperComp.h"

#include "GameObject.h"
#include "GlobalTime.h"
#include "InputManager.h"
#include "PlayerObserver.h"
#include "TextureComponent.h"
#include <AnimationComponent.h>

#include "LadderComp.h"
#include "LadderTop.h"

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
	if (!m_IsTouchingLadder) return;

}

void PeterPepperComp::TryClimb(int direction)
{
	if(m_IsTouchingTopLadder && direction == -1 || m_IsTouchingLadder)
	{
		auto pos = m_pGameObject->GetPosition();
		m_pGameObject->SetPosition(pos.x, pos.y + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction);
	}
}

void PeterPepperComp::StartRunAnim(int direction)
{
	auto text = m_pGameObject->GetComponent<dae::TextureComponent>();
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	anim->SetCurrentAnimation("run");
	text->m_Flipped = direction == 1;
}

void PeterPepperComp::Run(int direction)
{
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction, pos.y);
}

void PeterPepperComp::Update()
{


	m_IsTouchingLadder = false;
	m_IsTouchingTopLadder = false;
}

void PeterPepperComp::OnCollision(dae::GameObject* other)
{
	if (other->GetComponent<LadderComp>())
	{
		m_IsTouchingLadder = true;
	}
	if (other->GetComponent<LadderTop>())
	{
		m_IsTouchingTopLadder = true;
	}
}

