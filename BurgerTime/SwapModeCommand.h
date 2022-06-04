#pragma once
#include <Command.h>
#include "SelectModeComp.h"
class SwapModeCommand :
    public dae::Command
{
	SelectModeComp* m_SelectModeComp;
	int direction;
public:
	SwapModeCommand(SelectModeComp* selectModeComp, int direction) : Command(), m_SelectModeComp(selectModeComp), direction(direction) {}
	void Execute() override{};
	void FirstExecute() override
	{
		m_SelectModeComp->IncrementSelection(direction);
	}
};

