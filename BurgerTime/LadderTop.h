#pragma once
#include <BaseComponent.h>
class LadderTop final :
    public dae::BaseComponent
{
public:
	LadderTop(dae::GameObject* gameObject)
		: BaseComponent(gameObject)
	{
	}
};

