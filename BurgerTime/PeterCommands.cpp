#include "PeterCommands.h"


LateralMovementCommand::LateralMovementCommand(std::shared_ptr<PeterPepperComp> pepperComp, int direction) : m_pPepper(pepperComp), m_Direction(direction)
{
}

void LateralMovementCommand::Execute()
{
	m_pPepper->Run(m_Direction);
}

void LateralMovementCommand::FirstExecute()
{
	m_pPepper->StartRunAnim(m_Direction);
}
