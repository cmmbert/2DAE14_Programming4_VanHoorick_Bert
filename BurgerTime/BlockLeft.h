#pragma once
#include <BaseComponent.h>
class BlockLeft final :
    public dae::BaseComponent
{
public:
	explicit BlockLeft(dae::GameObject* gameObject)
		: BaseComponent(gameObject)
	{
	}
};

