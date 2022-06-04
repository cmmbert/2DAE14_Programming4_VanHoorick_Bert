#pragma once
#include "Command.h"
#include "SelectModeComp.h"

class SelectModeCommand : public dae::Command
{
	SelectModeComp* m_Button;
public:
	SelectModeCommand(SelectModeComp* button) : Command(), m_Button(button){};
	void Execute() override{};
	void FirstExecute() override
	{
		m_Button->SelectCurrentMode();
	}
};

