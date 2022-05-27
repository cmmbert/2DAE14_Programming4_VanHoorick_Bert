#pragma once
#include "BaseComponent.h"

class EnemyComponent final : public dae::BaseComponent 
{
	bool m_IsDead{};
public:
	EnemyComponent() = delete;
	EnemyComponent(dae::GameObject* gameObject);
	void OnCollision(dae::GameObject* other) override;
};

