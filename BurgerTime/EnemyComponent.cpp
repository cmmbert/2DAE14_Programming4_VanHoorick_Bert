#include "EnemyComponent.h"

#include "AnimationComponent.h"
#include "BlockComp.h"
#include "BurgerShardComp.h"
#include "GameObject.h"
#include "GlobalTime.h"
#include "LadderComp.h"
#include "LadderTop.h"

bool EnemyComponent::CanChangeDirection()
{
	int deviation = 10;
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
	std::cout << "New dir: ";
	const auto targetPos = m_Target->GetPosition();
	const auto pos = m_pGameObject->GetPosition();
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
	if(targetPos.x < pos.x)
	{
		m_CurrentChaseDir = { -1 ,0 };
		return;
	}
	if(targetPos.x > pos.x)
	{
		m_CurrentChaseDir = { 1 ,0 };
		return;
	}
}

EnemyComponent::EnemyComponent(dae::GameObject* gameObject, std::shared_ptr<dae::GameObject> target): BaseComponent(gameObject), m_Target(target)
{
}

bool EnemyComponent::IsOnFloor()
{
	int deviation = 10;
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

void EnemyComponent::ChaseTarget()
{
	if(m_CurrentChaseDir.x != 0)
	{
		Run(m_CurrentChaseDir.x);
	}
}

void EnemyComponent::Run(int direction)
{
	if (!IsOnFloor()) return;
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x + m_Speed * GlobalTime::GetInstance().GetElapsed() * direction, pos.y);

	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	anim->SetCurrentAnimation("run");
}

void EnemyComponent::OnCollision(dae::GameObject* other)
{
	if(!m_IsDead && other->GetComponent<BurgerShardComp>())
	{
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

}

void EnemyComponent::Update()
{
	if(m_IsDead)
	{
		m_TimeDead += GlobalTime::GetInstance().GetElapsed();
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
			std::cout << m_CurrentChaseDir.x << ";" << m_CurrentChaseDir.y << "\n";
		}
		ChaseTarget();
	}


	m_IsTouchingBlock = false;
	m_IsTouchingLadder = false;
	m_IsTouchingTopLadder = false;
}

