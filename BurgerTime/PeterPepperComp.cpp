#include "MiniginPCH.h"
#include "PeterPepperComp.h"

#include "InputManager.h"
#include "PlayerObserver.h"

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

void PeterPepperComp::Update()
{
	if (dae::InputManager::GetInstance().IsPressed(eControllerButton::ButtonA)) OnDeath();
}

void PeterPepperComp::Render() const
{

}
