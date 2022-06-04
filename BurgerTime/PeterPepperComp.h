#pragma once
#include "BaseComponent.h"
#include "LevelSettings.h"
#include "Subject.h"
#include "glm/vec2.hpp"

class PeterPepperComp : public dae::BaseComponent, public Subject
{

private:
	void OnDeath();

	int m_Speed{ 30 * LevelSettings::Scale };
	bool m_IsTouchingTopLadder{};
	bool m_IsTouchingBlock{};
	bool m_IsTouchingLadder{};
	bool IsOnFloor();
	bool CanClimbUp() { return m_IsTouchingLadder; }
	bool CanClimbDown() { return (m_IsTouchingLadder || m_IsTouchingTopLadder) && !m_IsTouchingBlock; }
	bool m_IsTouchingLeftBlock{};
	bool CanMoveLeft() { return !m_IsTouchingLeftBlock; }
	bool m_IsTouchingRightBlock{};
	bool CanMoveRight() { return !m_IsTouchingRightBlock; }

	bool m_HasRecievedInputThisFrame{ };

	int m_CurrentLadderXPos{};
	std::shared_ptr<dae::GameObject> m_SaltGo;
	int m_LivesLeft{ 3 };
	bool m_IsDead{};
	glm::ivec2 m_LastDir{1,0};
	size_t m_SaltsLeft{ 5 };

	float m_TimeSincePlayerDied{};
	float m_TimeBeforeRespawn{ 3 };
public:
	PeterPepperComp() = delete;
	PeterPepperComp(dae::GameObject* gameObject);
	~PeterPepperComp() = default;
	PeterPepperComp(const PeterPepperComp& other) = delete;
	PeterPepperComp(PeterPepperComp&& other) noexcept = delete;
	PeterPepperComp& operator=(const PeterPepperComp& other) = delete;
	PeterPepperComp& operator=(PeterPepperComp&& other) noexcept = delete;

	void ThrowSalt();
	void StartClimbAnim(int direction);
	void TryClimb(int direction);
	void StartRunAnim(int direction);
	void TryRun(int direction);
	void Update() override;
	void OnCollision(dae::GameObject* other) override;
	void Reset();

};

