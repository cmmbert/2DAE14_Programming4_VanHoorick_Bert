#pragma once
#include <memory>

#include "Command.h"

namespace dae
{
	class GameObject;
}

class LateralMovementCommand : public dae::Command
{
public:
	LateralMovementCommand(std::shared_ptr<dae::GameObject> pGo, float speed);
	void Execute() override;

private:
	std::shared_ptr<dae::GameObject> m_pGameObject{};
	float m_Speed;
};

