#include "MiniginPCH.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "InputManager.h"
#include <XInput.h>

#include <strsafe.h>

class dae::InputManager::impl
{
public:
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};

	BYTE m_PrevKeyboardState[256];
	BYTE m_CurrentKeyboardState[256];
};


dae::InputManager::InputManager()
	: m_pImpl({ std::make_unique<impl>() })
{
}

dae::InputManager::~InputManager() = default;




bool dae::InputManager::Update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
		}
		if (e.type == SDL_KEYUP) {
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}
	
	memcpy(m_pImpl->m_PrevKeyboardState, m_pImpl->m_CurrentKeyboardState, sizeof(BYTE[256]));
	GetKeyboardState(m_pImpl->m_CurrentKeyboardState);

	for (auto& keyCommand : m_KeyCommandMap)
	{
		if(m_pImpl->m_CurrentKeyboardState[static_cast<int>(keyCommand.first)] & 0xF0)
		{
			if(m_pImpl->m_PrevKeyboardState[static_cast<int>(keyCommand.first)] & 0xF0)
			{
				keyCommand.second->Execute();
			}
			else
			{
				keyCommand.second->FirstExecute();
			}
		}
	}



	CopyMemory(&m_pImpl->previousState, &m_pImpl->currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_pImpl->currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_pImpl->currentState);

	auto buttonChanges = m_pImpl->currentState.Gamepad.wButtons ^ m_pImpl->previousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_pImpl->currentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_pImpl->currentState.Gamepad.wButtons);
	m_ButtonsPressed = m_pImpl->currentState.Gamepad.wButtons;

	for (auto& command : m_ControllerCommandMap)
	{
		if (IsPressed(command.first))
			command.second->Execute();
		if (IsPressedThisFrame(command.first))
			command.second->FirstExecute();
	}
	
	return true;
}

bool dae::InputManager::IsPressed(const eControllerButton& buttonMask) const
{
	return m_ButtonsPressed & static_cast<int>(buttonMask);
}

bool dae::InputManager::IsPressedThisFrame(const eControllerButton& buttonMask) const
{
	return m_ButtonsPressedThisFrame & static_cast<int>(buttonMask);
}

void dae::InputManager::AddOrChangeCommand(eControllerButton button, std::shared_ptr<Command> command)
{
	m_ControllerCommandMap[button] = command;
}

void dae::InputManager::AddOrChangeCommand(eKeyboardButton button, std::shared_ptr<Command> command)
{
	m_KeyCommandMap[button] = command;
}

void dae::InputManager::RemoveCommand(eControllerButton button)
{
	m_ControllerCommandMap.erase(button);
}

void dae::InputManager::RemoveCommand(eKeyboardButton button)
{
	m_KeyCommandMap.erase(button);
}

