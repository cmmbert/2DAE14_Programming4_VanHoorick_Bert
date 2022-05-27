#include "MiniginPCH.h"
#include "PeterPepperComp.h"

#include "GameObject.h"
#include "GlobalTime.h"
#include "InputManager.h"
#include "PlayerObserver.h"
#include "TextureComponent.h"
#include <AnimationComponent.h>

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
	if (dae::InputManager::GetInstance().IsPressed(eControllerButton::ButtonA)) OnDeath();
}

