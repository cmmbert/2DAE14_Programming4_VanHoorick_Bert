#include "MiniginPCH.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "InputManager.h"
#include <XInput.h>


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
	CopyMemory(&m_pImpl->previousState, &m_pImpl->currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_pImpl->currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_pImpl->currentState);

	auto buttonChanges = m_pImpl->currentState.Gamepad.wButtons ^ m_pImpl->previousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_pImpl->currentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_pImpl->currentState.Gamepad.wButtons);


	if (IsPressed(ControllerButton::ButtonB)) return false;
	return true; //TODO implement button to stop game
}

bool dae::InputManager::IsPressed(ControllerButton buttonMask) const
{
	return m_ButtonsPressedThisFrame & static_cast<int>(buttonMask);
}

