#pragma once
#include "eEvent.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
}

class PlayerObserver final : public Observer
{
public:
	void OnNotify(const dae::GameObject& entity, eEvent event) override;
};

