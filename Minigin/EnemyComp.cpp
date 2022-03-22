#include "MiniginPCH.h"
#include "EnemyComp.h"

#include "InputManager.h"

void EnemyComp::OnDeath()
{
	std::cout << "EnemyDied\n";
	NotifyAllObservers(*m_pGameObject, eEvent::EnemyDied);
}

void EnemyComp::Update()
{
	if (dae::InputManager::GetInstance().IsPressed(dae::ControllerButton::ButtonX)) 
		OnDeath();

}

void EnemyComp::Render() const
{
}
