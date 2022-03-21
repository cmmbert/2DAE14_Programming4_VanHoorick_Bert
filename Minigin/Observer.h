#pragma once
#include "eEvent.h"

namespace dae
{
	class GameObject;
}

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = default;
	virtual void OnNotify(const dae::GameObject& entity, eEvent event){};
};

