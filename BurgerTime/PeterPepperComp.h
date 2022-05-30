#pragma once
#include "BaseComponent.h"
#include "LevelSettings.h"
#include "Subject.h"

class PeterPepperComp : public dae::BaseComponent, public Subject
{

private:
	void OnDeath();

	int m_Speed{ 30 * LevelSettings::Scale };
	bool m_IsTouchingTopLadder{};
	bool m_IsTouchingBlock{};
	bool m_IsTouchingLadder{};
	std::vector<int> m_LevelHeights{};
	bool IsOnFloor();
	bool CanClimbUp() { return m_IsTouchingLadder; }
	bool CanClimbDown() { return (m_IsTouchingLadder || m_IsTouchingTopLadder) && !m_IsTouchingBlock; }
	bool m_IsTouchingLeftBlock{};
	bool CanMoveLeft() { return !m_IsTouchingLeftBlock; }
	bool m_IsTouchingRightBlock{};
	bool CanMoveRight() { return !m_IsTouchingRightBlock; }
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
	void TryRun(int direction);
	void Update() override;
	void OnCollision(dae::GameObject* other) override;

	void AddLevelHeight(int newHeight);
	int m_LivesLeft{ 3 };

};

