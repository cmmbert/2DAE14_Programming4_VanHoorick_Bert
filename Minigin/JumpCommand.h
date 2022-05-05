#pragma once
#include "Command.h"

class JumpCommand final : public dae::Command
{
public:
	JumpCommand();
	~JumpCommand() override = default;
	void Execute() override;
};

