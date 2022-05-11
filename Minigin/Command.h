#pragma once

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute() = 0;
	};
}
