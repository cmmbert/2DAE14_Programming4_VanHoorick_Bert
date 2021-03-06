#include "EnemyComponent.h"

#include "AnimationComponent.h"
#include "BlockComp.h"
#include "GameObject.h"
#include "GlobalTime.h"
#include "LadderComp.h"
#include "LadderTop.h"
#include "BurgerPiece.h"
#include "FloorComp.h"
#include "SaltComp.h"


bool EnemyComponent::CanClimbDown()
{
	return (m_IsTouchingLadder || m_IsTouchingTopLadder) && !m_IsTouchingBlock && m_CurrentChaseDir.y != 1;
}


bool EnemyComponent::CanMoveLeft()
{
	return !m_IsTouchingLeftBlock && m_CurrentChaseDir.x != 1;
}

bool EnemyComponent::CanChangeDirection()
{
	if (!IsOnFloor() || !m_IsTouchingLadder || m_TimeSinceLastDirChange < m_DirChangeCd) return false;
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

void EnemyComponent::SetRandomDirection()
{
	if (CanClimbDown()) { ChangeDirection({ 0,-1 }); return; }
	if (CanClimbUp())   {ChangeDirection({  0,1 }); return; };
	if (CanMoveRight()) {ChangeDirection({  1,0 }); return; };
	if (CanMoveLeft())  {ChangeDirection({ -1,0 }); return; };
	
	ChangeDirection(m_CurrentChaseDir * -1); //Reverse direction in case we cannot change to any valid direction
}


void EnemyComponent::ChangeDirection(glm::ivec2 newDir)
{

	auto text = m_pGameObject->GetComponent<dae::TextureComponent>();
	text->m_Flipped = false;
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();

	if (newDir == glm::ivec2{ 1,0 })
	{
		anim->SetCurrentAnimation("run");
		text->m_Flipped = true;
	}

	if (newDir == glm::ivec2{ -1,0 })
	{
		anim->SetCurrentAnimation("run");
	}

	if (newDir == glm::ivec2{ 0,1 })
	{
		anim->SetCurrentAnimation("climbup");
	}

	if (newDir == glm::ivec2{ 0,-1 })
	{
		anim->SetCurrentAnimation("climbdown");
	}
		
	m_CurrentChaseDir = newDir;
	m_TimeSinceLastDirChange = 0;
}

void EnemyComponent::CalculateNewDir()
{
	const auto targetPos = m_Target->GetPosition();
	const auto pos = m_pGameObject->GetPosition();

	int deviation = 2;
	if(abs(targetPos.y - pos.y) > deviation)
	{
		if(CanClimbUp() && targetPos.y > pos.y)
		{
			ChangeDirection({ 0,1 });
			return;
		}
		if(CanClimbDown() && targetPos.y < pos.y)
		{
			ChangeDirection({ 0,-1 });
			return;
		}
	}
	if(targetPos.x < pos.x)
	{
		if (CanMoveLeft())
		{
			ChangeDirection({ -1 ,0 });
		}
		else
		{
			SetRandomDirection();
		}

		return;
	}
	if(targetPos.x > pos.x)
	{
		if(CanMoveRight())
		{
			ChangeDirection({ 1 ,0 });
		}
		else
		{
			SetRandomDirection();
		}

		return;
	}
}

EnemyComponent::EnemyComponent(dae::GameObject* gameObject, std::shared_ptr<dae::GameObject> target, glm::ivec2 spawnPoint)
	: BaseComponent(gameObject), m_EnemyCollision(m_pGameObject->GetComponent<EnemyCollision>()), m_Target(target), m_SpawnPoint(spawnPoint)
{
}

bool EnemyComponent::IsOnFloor()
{
	if (!m_IsTouchingFloor) return false; //cannot be on floor if not touching it 
	int deviation = 2;
	for (int levelHeight : LevelSettings::m_LevelHeights)
	{
		if (abs(levelHeight - m_pGameObject->GetWorldPosition().y) <= deviation)
		{
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
	if(other->GetComponent<FloorComp>())
	{
		m_IsTouchingFloor = true;
	}
}

void EnemyComponent::OnDeath()
{
	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	anim->SetCurrentAnimation("death");
	anim->SetAnimationSpeed(0.2f);
	m_IsDead = true;
}

void EnemyComponent::Respawn()
{
	m_IsDead = false;
	m_TimeDead = 0;
	m_pGameObject->SetPosition(m_SpawnPoint);

	auto anim = m_pGameObject->GetComponent<AnimationComponent>();
	anim->SetCurrentAnimation("run");
	anim->SetAnimationSpeed(0.08f);
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
		if(!m_IsStopped)
		{
			if(!m_EnemyCollision->IsSalted())
			{
				m_TimeSinceLastDirChange += GlobalTime::GetInstance().GetElapsed();

				if (CanChangeDirection())
				{
					CalculateNewDir();
				}

				if (m_CurrentChaseDir == glm::ivec2{ 0,0 }) CalculateNewDir(); //Invalid direction, so get a new one
				if(!CanMoveRight() && m_CurrentChaseDir == glm::ivec2{1,0}) SetRandomDirection();
				if(!CanMoveLeft() && m_CurrentChaseDir == glm::ivec2{-1,0}) 
					SetRandomDirection();
				if(!CanClimbUp() && m_CurrentChaseDir == glm::ivec2{0,1}) SetRandomDirection();
				if(!CanClimbDown() && m_CurrentChaseDir == glm::ivec2{0,-1}) SetRandomDirection();

			
				ChaseTarget();
			}
		}
	}


	m_IsTouchingBlock = false;
	m_IsTouchingLadder = false;
	m_IsTouchingTopLadder = false;
	m_IsTouchingFloor = false;
	m_IsTouchingLeftBlock = false;
	m_IsTouchingRightBlock = false;
}

void EnemyComponent::Reset()
{
	Respawn();
	m_IsStopped = false;

}

