#pragma once
#include <BaseComponent.h>
class BlockRight final :
    public dae::BaseComponent
{
public:
	explicit BlockRight(dae::GameObject* gameObject)
		: BaseComponent(gameObject)
	{
	}
};

