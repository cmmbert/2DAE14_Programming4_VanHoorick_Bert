#include "EnemyCollision.h"

#include "SaltComp.h"
#include "GlobalTime.h"
#include "AnimationComponent.h"

void EnemyCollision::OnCollision(dae::GameObject* other)
{

	if (other->GetComponent<SaltComp>())
	{
		m_SaltStunTimeLeft = m_SaltStunTime;
		auto anim = m_pGameObject->GetComponent<AnimationComponent>();
		anim->SetCurrentAnimation("salted");
	}
}

void EnemyCollision::Update()
{
	if (IsSalted())
	{
		m_SaltStunTimeLeft -= GlobalTime::GetInstance().GetElapsed();
		if (m_SaltStunTimeLeft < 0)
		{
			auto anim = m_pGameObject->GetComponent<AnimationComponent>();
			anim->SetCurrentAnimation("run");
		}
	}
}
