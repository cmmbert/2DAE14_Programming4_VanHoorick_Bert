#include "EnemyComponent.h"

#include "AnimationComponent.h"
#include "BlockComp.h"
#include "GameObject.h"
#include "GlobalTime.h"
#include "LadderComp.h"
#include "LadderTop.h"
#include "BurgerPiece.h"

bool EnemyComponent::CanChangeDirection()
{
	if (!IsOnFloor()) return false;
	int deviation = 1;
	for (int levelWidth : LevelSettings::m_LevelLadderCrossPoints)
	{
		if (abs(levelWidth - m_pGameObject->GetWorldPosition().x) <= deviation)
		{
			return true;
		}
	}
	return false;
}

void EnemyComponent::ChangeDirection()
{
	const auto targetPos = m_Target->GetPosition();
	const auto pos = m_pGameObject->GetPosition();

	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	auto text = m_pGameObject->GetComponent<dae::TextureComponent>();
	int deviation = 1;
	if(abs(targetPos.y - pos.y) > deviation)
	{
		if(CanClimbUp() && targetPos.y > pos.y)
		{
			m_CurrentChaseDir = { 0,1 };
			return;
		}
		if(CanClimbDown() && targetPos.y < pos.y)
		{
			m_CurrentChaseDir = { 0,-1 };
			return;
		}
	}
	if(targetPos.x < pos.x)
	{
		anim->SetCurrentAnimation("run");
		if (CanMoveLeft())
		{
			m_CurrentChaseDir = { -1 ,0 };
			text->m_Flipped = false;
		}
		else
		{
			m_CurrentChaseDir = { 1,0 };
			text->m_Flipped = true;
		}

		return;
	}
	if(targetPos.x > pos.x)
	{
		anim->SetCurrentAnimation("run");
		if(CanMoveRight())
		{
			m_CurrentChaseDir = { 1 ,0 };
			text->m_Flipped = true;
		}
		else
		{
			m_CurrentChaseDir = { -1 ,0 };
			text->m_Flipped = false;
		}

		return;
	}
}

EnemyComponent::EnemyComponent(dae::GameObject* gameObject, std::shared_ptr<dae::GameObject> target, glm::ivec2 spawnPoint)
	: BaseComponent(gameObject), m_Target(target), m_SpawnPoint(spawnPoint)
{
}

bool EnemyComponent::IsOnFloor()
{
	int deviation = 1;
	for (int levelHeight : LevelSettings::m_LevelHeights)
	{
		if (abs(levelHeight - m_pGameObject->GetWorldPosition().y) <= deviation)
		{
			//m_pGameObject->SetPosition(m_pGameObject->GetPosition().x, levelHeight);
			return true;
		}
	}
	return false;
}

void EnemyComponent::Climb(int direction)
{
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x, pos.y + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction);
}

void EnemyComponent::ChaseTarget()
{
	if(m_CurrentChaseDir.x != 0)
	{
		Run(m_CurrentChaseDir.x);
	}
	else
	{
		Climb(m_CurrentChaseDir.y);
	}
}

void EnemyComponent::Run(int direction)
{
	if (!IsOnFloor()) return;
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction, pos.y);

}

void EnemyComponent::OnCollision(dae::GameObject* other)
{
	if (auto burger = other->GetComponent<BurgerPiece>())
	{
		if (m_IsDead || !burger->IsFalling()) return;
		OnDeath();
	}
	if (other->GetComponent<LadderComp>())
	{
		int deviation = 5;
		if (abs(other->GetWorldPosition().x - m_pGameObject->GetWorldPosition().x) <= deviation)
			m_IsTouchingLadder = true;
	}
	if (other->GetComponent<LadderTop>())
	{
		int deviation = 5;
		if (abs(other->GetWorldPosition().x - m_pGameObject->GetWorldPosition().x) <= deviation)
		{
			m_IsTouchingTopLadder = true;
		}
	}
	if (auto block = other->GetComponent<BlockComp>())
	{
		if (block->IsBlockingDirection(Direction::Down))
			m_IsTouchingBlock = true;
		if (block->IsBlockingDirection(Direction::Right))
			m_IsTouchingRightBlock = true;
		if (block->IsBlockingDirection(Direction::Left))
			m_IsTouchingLeftBlock = true;
	}
}

void EnemyComponent::OnDeath()
{
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	anim->SetCurrentAnimation("death");
	m_IsDead = true;
}

void EnemyComponent::Respawn()
{
	m_IsDead = false;
	m_TimeDead = 0;
	m_pGameObject->SetPosition(m_SpawnPoint);

	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	anim->SetCurrentAnimation("run");
}

void EnemyComponent::Update()
{
	if(m_IsDead)
	{
		m_TimeDead += GlobalTime::GetInstance().GetElapsed();
		if(m_TimeDead > m_DeathAnimTime)
		{
			m_pGameObject->SetPosition({ -1000,-1000 });
		}
		if(m_TimeDead > m_RespawnTime)
		{
			Respawn();
		}
	}
	else
	{
		if (m_CurrentChaseDir == glm::ivec2{ 0,0 }) ChangeDirection(); //Invalid direction, so get a new one
		if(CanChangeDirection())
		{
			ChangeDirection();
		}
		ChaseTarget();
	}


	m_IsTouchingBlock = false;
	m_IsTouchingLadder = false;
	m_IsTouchingTopLadder = false;
}

