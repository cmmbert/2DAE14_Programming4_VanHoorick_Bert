#include "MiniginPCH.h"
#include "ClimbCommand.h"

ClimbCommand::ClimbCommand(std::shared_ptr<dae::GameObject> pGo) : m_pGameObject({ pGo })
{
}

void ClimbCommand::Execute()
{
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x, pos.y + 5);
	std::cout << "climb\n";
}
