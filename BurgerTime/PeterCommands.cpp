#include "PeterCommands.h"


LateralMovementCommand::LateralMovementCommand(std::shared_ptr<PeterPepperComp> pepperComp, int direction) : m_pPepper(pepperComp), m_Direction(direction)
{
}

void LateralMovementCommand::Execute()
{
	m_pPepper->TryRun(m_Direction);
}

void LateralMovementCommand::FirstExecute()
{
	m_pPepper->StartRunAnim(m_Direction);
}

VerticalMovementCommand::VerticalMovementCommand(std::shared_ptr<PeterPepperComp> pepperComp, int direction) : m_pPepper(pepperComp), m_Direction(direction)
{
}

void VerticalMovementCommand::Execute()
{
	m_pPepper->TryClimb(m_Direction);
}

void VerticalMovementCommand::FirstExecute()
{
	m_pPepper->StartClimbAnim(m_Direction);
}
