#pragma once
#include "BaseComponent.h"

class AnimationComponent : public dae::BaseComponent
{
public:
	void Update() override;
	void Start() override;
	void Render() const override;
	~AnimationComponent() override;
};

