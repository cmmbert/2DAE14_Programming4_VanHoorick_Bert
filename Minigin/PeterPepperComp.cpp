#include "MiniginPCH.h"
#include "PeterPepperComp.h"

#include "InputManager.h"
#include "PlayerObserver.h"

PeterPepperComp::PeterPepperComp()
{
	//AddObserver(PlayerObserver());
}

void PeterPepperComp::OnDeath()
{
	--m_LivesLeft;
	std::cout << "PlayerDied, lives left: " << m_LivesLeft << "\n";
	NotifyAllObservers(*m_pGameObject, eEvent::PepperDied);
}

void PeterPepperComp::Update()
{
	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonA)) OnDeath();
}

void PeterPepperComp::Render() const
{

}
