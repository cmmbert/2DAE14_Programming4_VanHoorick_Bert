#include "MiniginPCH.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "InputManager.h"
#include <XInput.h>

#include "ClimbCommand.h"


class dae::InputManager::impl
{
public:
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};
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
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}


	CopyMemory(&m_pImpl->previousState, &m_pImpl->currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_pImpl->currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_pImpl->currentState);

	auto buttonChanges = m_pImpl->currentState.Gamepad.wButtons ^ m_pImpl->previousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_pImpl->currentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_pImpl->currentState.Gamepad.wButtons);
	m_ButtonsPressed = m_pImpl->currentState.Gamepad.wButtons;

	for (auto& command : m_CommandMap)
	{
		if (IsPressed(command.first))
			command.second->Execute();
		if (IsPressedThisFrame(command.first))
			command.second->FirstExecute();
	}

	if (IsPressed(eControllerButton::ButtonB)) return false;
	return true; //TODO implement button to stop game
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
	m_CommandMap[button] = command;
}

void dae::InputManager::RemoveCommand(eControllerButton button)
{
	m_CommandMap.erase(button);
}

