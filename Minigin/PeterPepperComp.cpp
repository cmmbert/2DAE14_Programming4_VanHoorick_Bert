#include "MiniginPCH.h"
#include "PeterPepperComp.h"

#include "InputManager.h"

void PeterPepperComp::OnDeath()
{
	--m_LivesLeft;
	std::cout << "PlayerDied, lives left: " << m_LivesLeft << "\n";
}

void PeterPepperComp::Update()
{
	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonA)) OnDeath();
}

void PeterPepperComp::Render() const
{
}
