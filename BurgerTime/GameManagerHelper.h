#pragma once
#include "BaseComponent.h"
//I'm so done, I cant update the gamemanager and I cant reach it from the collisionmanager so this stupidity has to be done
class GameManagerHelper final : public dae::BaseComponent
{
	float m_TimeToWait{0.5f};
	float m_TimeLeftToWait{};
	bool m_Trigger{};
public:
	explicit GameManagerHelper(dae::GameObject* gameObject)
		: BaseComponent(gameObject)
	{
	}
	void WaitOnNextLevel() { m_TimeLeftToWait = m_TimeToWait; m_Trigger = true; }
	void Update() override;
};

