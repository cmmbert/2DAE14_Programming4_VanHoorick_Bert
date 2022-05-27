#pragma once
#include "BaseComponent.h"
#include "Subject.h"

class PeterPepperComp : public dae::BaseComponent, public Subject
{
public:
	PeterPepperComp() = delete;
	PeterPepperComp(dae::GameObject* gameObject);
	~PeterPepperComp() = default;
	PeterPepperComp(const PeterPepperComp& other) = delete;
	PeterPepperComp(PeterPepperComp&& other) noexcept = delete;
	PeterPepperComp& operator=(const PeterPepperComp& other) = delete;
	PeterPepperComp& operator=(PeterPepperComp&& other) noexcept = delete;

private:
	void OnDeath();
public:
	void StartRunAnim(int direction);
	void Run(int direction);
	void Update() override;

	int m_LivesLeft{ 3 };
	int m_Speed{300};
};

