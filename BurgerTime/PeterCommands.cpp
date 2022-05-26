#include "PeterCommands.h"

#include "GameObject.h"
#include "GlobalTime.h"

LateralMovementCommand::LateralMovementCommand(std::shared_ptr<dae::GameObject> pGo, float speed) : m_pGameObject(pGo), m_Speed(speed)
{
}

void LateralMovementCommand::Execute()
{
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x + m_Speed * GlobalTime::GetInstance().GetElapsed(), pos.y);
}
