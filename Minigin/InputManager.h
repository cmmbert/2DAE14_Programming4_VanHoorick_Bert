#pragma once
#include <memory>
#include "Singleton.h"

namespace dae
{

	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,

		DpadUp = 0x0001,
		DpadDown = 0x0002,
		DpadLeft = 0x0004,
		DpadRight = 0x0008,

		Start = 0x0010,
		Back = 0x0020,

		LeftTrigger = 0x0040,
		RightTrigger = 0x0080,

		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,

	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		bool Update(); //Returns false to stop the game loop
		bool IsPressed(ControllerButton buttonMask) const;
	private:
		class impl;
		std::unique_ptr<impl> m_pImpl;
		int m_ButtonsPressedThisFrame{};
		int m_ButtonsReleasedThisFrame{};

		//std::vector < std::unique_ptr<Command>> m_Commands{};
	};

}
