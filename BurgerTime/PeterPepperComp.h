#pragma once
#include "BaseComponent.h"
#include "Subject.h"

class PeterPepperComp : public dae::BaseComponent, public Subject
{

private:
	void OnDeath();

	int m_Speed{ 300 };
	bool m_IsTouchingLadder{};
	bool m_IsTouchingTopLadder{};
public:
	PeterPepperComp() = delete;
	PeterPepperComp(dae::GameObject* gameObject);
	~PeterPepperComp() = default;
	PeterPepperComp(const PeterPepperComp& other) = delete;
	PeterPepperComp(PeterPepperComp&& other) noexcept = delete;
	PeterPepperComp& operator=(const PeterPepperComp& other) = delete;
	PeterPepperComp& operator=(PeterPepperComp&& other) noexcept = delete;


	void StartClimbAnim(int direction);
	void TryClimb(int direction);
	void StartRunAnim(int direction);
	void Run(int direction);
	void Update() override;
	void OnCollision(dae::GameObject* other) override;
	int m_LivesLeft{ 3 };

};

