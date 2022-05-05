#pragma once
#include "eControllerButton.h"


namespace dae
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute() = 0;
		//void SetButtonMask(eControllerButton buttonMask) { m_ButtonMask = buttonMask; }
		//eControllerButton GetButtonMask() const { return m_ButtonMask; }
	private:
		//eControllerButton m_ButtonMask{};
	};
}
