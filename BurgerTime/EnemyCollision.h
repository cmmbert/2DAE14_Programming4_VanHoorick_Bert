#pragma once
#include "BaseComponent.h"

class EnemyCollision final : public dae::BaseComponent
{
public:
	explicit EnemyCollision(dae::GameObject* gameObject)
		: BaseComponent(gameObject)
	{
	}
};
