#pragma once
#include "BaseComponent.h"

class BurgerShardComp : public dae::BaseComponent
{
public:
	void Start() override;
	void Update() override;
	void Render() const override;
};

