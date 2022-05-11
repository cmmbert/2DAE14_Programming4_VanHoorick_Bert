#pragma once
#include <map>
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
		bool IsPressed(const eControllerButton& buttonMask) const;
		void AddOrChangeCommand(eControllerButton button, std::shared_ptr<Command> command);
		void RemoveCommand(eControllerButton button);
	private:
		class impl;
		std::unique_ptr<impl> m_pImpl;
		int m_ButtonsPressedThisFrame{};
		int m_ButtonsReleasedThisFrame{};
		std::map<eControllerButton, std::shared_ptr<Command>> m_CommandMap{};

	};

}
