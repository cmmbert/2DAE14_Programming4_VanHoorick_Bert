#pragma once
#include <memory>

#include "Command.h"
#include "PeterPepperComp.h"

namespace dae
{
	class GameObject;
}

class LateralMovementCommand : public dae::Command
{
public:
	LateralMovementCommand(std::shared_ptr<PeterPepperComp> pepperComp, int direction);
	void Execute() override;
	void FirstExecute() override;

private:
	std::shared_ptr<PeterPepperComp> m_pPepper{};
	int m_Direction;
};

class VerticalMovementCommand : public dae::Command
{
public:
	VerticalMovementCommand(std::shared_ptr<PeterPepperComp> pepperComp, int direction);

	void Execute() override;
	void FirstExecute() override;

private:
	std::shared_ptr<PeterPepperComp> m_pPepper{};
	int m_Direction;
};



