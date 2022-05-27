#include "EnemyComponent.h"

#include "AnimationComponent.h"
#include "GameObject.h"

EnemyComponent::EnemyComponent(dae::GameObject* gameObject): BaseComponent(gameObject)
{
}

void EnemyComponent::OnCollision(dae::GameObject* other)
{
	if(!m_IsDead)
	{
		auto anim = m_pGameObject->GetComponent<AnimationComponent>();
		anim->SetCurrentAnimation("death");
		m_IsDead = true;
	}
}
