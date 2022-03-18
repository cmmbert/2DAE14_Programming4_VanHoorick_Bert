#pragma once
#include "BaseComponent.h"

class PeterPepperComp : public dae::BaseComponent
{
public:
	PeterPepperComp() = default;
	~PeterPepperComp() = default;
	PeterPepperComp(const PeterPepperComp& other) = delete;
	PeterPepperComp(PeterPepperComp&& other) noexcept = delete;
	PeterPepperComp& operator=(const PeterPepperComp& other) = delete;
	PeterPepperComp& operator=(PeterPepperComp&& other) noexcept = delete;

private:
	void OnDeath();
public:
	void Update() override;
	void Render() const override;

	int m_LivesLeft{ 3 };
};

