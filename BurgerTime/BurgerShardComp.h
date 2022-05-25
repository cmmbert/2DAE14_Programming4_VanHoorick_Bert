#pragma once
#include "BaseComponent.h"

class BurgerShardComp : public dae::BaseComponent
{
public:
	BurgerShardComp()
	{
		
	}

	void Start() override;
	void Update() override;
	void Render() const override;
	void OnCollision(dae::GameObject* other) override;
};

