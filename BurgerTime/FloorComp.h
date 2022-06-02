#pragma once
#include "BaseComponent.h"

class FloorComp final : public dae::BaseComponent
{
public:
	explicit FloorComp(dae::GameObject* gameObject)
		: BaseComponent(gameObject)
	{
	}
};

