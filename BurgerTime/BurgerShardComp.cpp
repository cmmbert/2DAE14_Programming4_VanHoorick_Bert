#include "BurgerShardComp.h"
#include "BurgerPiece.h"
#include "PeterPepperComp.h"


BurgerShardComp::BurgerShardComp(dae::GameObject* gameObject, int idx, BurgerPiece* burgerPiece) : BaseComponent(gameObject), m_Index(idx),
                                                                                                   m_OriginalY(static_cast<int>(m_pGameObject->GetPosition().y)),
                                                                                                   m_BurgerPiece(burgerPiece)
{
}

void BurgerShardComp::Start()
{
}

void BurgerShardComp::Update()
{
	if(m_SteppedOn)
	{
		auto pos = m_pGameObject->GetPosition();
		pos.y = static_cast<float>(m_Nudge);
		m_pGameObject->SetPosition(pos);
	}
	else
	{
		auto pos = m_pGameObject->GetPosition();
		pos.y = 0;
		m_pGameObject->SetPosition(pos);
	}
}

void BurgerShardComp::Render() const
{
}

void BurgerShardComp::OnCollision(dae::GameObject* other)
{
	if (other->GetComponent<PeterPepperComp>() == nullptr) return;
	if(!m_SteppedOn)
	{
		m_SteppedOn = true;
		m_BurgerPiece->OnSteppedOn(m_Index);
	}
}



