#pragma once
#include "Command.h"
#include "GameObject.h"

class ClimbCommand final : public dae::Command
{
public:
	ClimbCommand(std::shared_ptr<dae::GameObject> pGo);
	~ClimbCommand() override = default;
	void Execute() override;

private:
	std::shared_ptr<dae::GameObject> m_pGameObject{};
};

