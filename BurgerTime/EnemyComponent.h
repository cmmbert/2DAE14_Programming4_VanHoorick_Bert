#pragma once
#include <memory>
#include <vector>
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "LevelSettings.h"

class EnemyComponent final : public dae::BaseComponent 
{
	bool m_IsDead{};
	float m_DeathAnimTime{ 0.6f };
	float m_RespawnTime{10};
	float m_TimeDead{0};
	std::shared_ptr<dae::GameObject> m_Target;
	bool m_IsTouchingLadder{};
	bool m_IsTouchingTopLadder{};
	bool m_IsTouchingBlock{};
	int m_Speed{30 * LevelSettings::Scale };
	bool CanClimbUp() { return m_IsTouchingLadder; }
	bool CanClimbDown() { return (m_IsTouchingLadder || m_IsTouchingTopLadder) && !m_IsTouchingBlock; }
	bool m_IsTouchingLeftBlock{};
	bool CanMoveLeft() { return !m_IsTouchingLeftBlock; }
	bool m_IsTouchingRightBlock{};
	bool CanMoveRight() { return !m_IsTouchingRightBlock; }
	glm::ivec2 m_SpawnPoint{};
	glm::ivec2 m_CurrentChaseDir{};

	bool CanChangeDirection();
	void ChangeDirection();
public:
	EnemyComponent() = delete;
	EnemyComponent(dae::GameObject* gameObject, std::shared_ptr<dae::GameObject> target, glm::ivec2 spawnPoint);

	bool IsOnFloor();
	void Climb(int direction);
	void ChaseTarget();


	void Run(int direction);
	void OnCollision(dae::GameObject* other) override;
	void OnDeath();
	void Respawn();
	void Update() override;
};

