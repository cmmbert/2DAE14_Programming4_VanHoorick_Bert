#pragma once
#include "eEvent.h"

namespace dae
{
	class GameObject;
}

class Observer
{
public:
	virtual ~Observer(){};
	virtual void OnNotify(const dae::GameObject& entity, eEvent event) = 0;
};

