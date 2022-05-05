#include "MiniginPCH.h"
#include "JumpCommand.h"

JumpCommand::JumpCommand()
{
	SetButtonMask(eControllerButton::ButtonA);
}

void JumpCommand::Execute()
{
	std::cout << "jump new\n";
}
