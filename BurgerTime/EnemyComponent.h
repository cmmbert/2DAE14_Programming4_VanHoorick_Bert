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
	bool CanClimbUp() { return m_IsTouchingLadder && m_CurrentChaseDir.y != -1; }
	bool CanClimbDown() { return (m_IsTouchingLadder || m_IsTouchingTopLadder) && !m_IsTouchingBlock && m_CurrentChaseDir.y != 1; }
	bool m_IsTouchingLeftBlock{};
	bool CanMoveLeft() { return !m_IsTouchingLeftBlock && m_CurrentChaseDir.x != 1; }
	bool m_IsTouchingRightBlock{};
	bool CanMoveRight() { return !m_IsTouchingRightBlock && m_CurrentChaseDir.x != -1; }
	glm::ivec2 m_SpawnPoint{};
	glm::ivec2 m_CurrentChaseDir{};
	bool m_IsTouchingFloor{};

	float m_TimeSinceLastDirChange{};
	float m_DirChangeCd{ 1 };
	bool CanChangeDirection();
	void CalculateNewDir();
	void ChangeDirection(glm::ivec2 newDir);
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

