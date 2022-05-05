#pragma once
#include <memory>

#include "Command.h"
#include "Singleton.h"
#include "eControllerButton.h"

namespace dae
{

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		bool Update(); //Returns false to stop the game loop
		bool IsPressed(eControllerButton buttonMask) const;
	private:
		class impl;
		std::unique_ptr<impl> m_pImpl;
		int m_ButtonsPressedThisFrame{};
		int m_ButtonsReleasedThisFrame{};

		//std::unique_ptr<Command> m_ButtonX;
		std::vector < std::unique_ptr<Command>> m_Commands{};
	};

}
