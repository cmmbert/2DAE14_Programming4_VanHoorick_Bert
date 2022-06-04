#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

class EnemyCollision final : public dae::BaseComponent
{

	float m_SaltStunTime{ 4 };
	float m_SaltStunTimeLeft{};
public:
	explicit EnemyCollision(dae::GameObject* gameObject)
		: BaseComponent(gameObject)
	{
	}

	void OnCollision(dae::GameObject* other) override;

	bool IsSalted() const { return m_SaltStunTimeLeft > 0; }
	void Update() override;
};