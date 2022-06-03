#pragma once
#include "BaseComponent.h"

class BurgerBlock: public dae::BaseComponent
{
public:
	explicit BurgerBlock(dae::GameObject* gameObject)
		: BaseComponent(gameObject)
	{
	}
};

