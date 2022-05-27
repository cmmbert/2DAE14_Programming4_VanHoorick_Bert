#include "BurgerShardComp.h"
#include "BurgerPiece.h"


class PeterPepperComp;

BurgerShardComp::BurgerShardComp(dae::GameObject* gameObject, int idx, BurgerPiece* burgerPiece) : BaseComponent(gameObject), m_Index(idx),
	m_OriginalY(m_pGameObject->GetPosition().y),
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
		pos.y = m_OriginalY + m_Nudge;
		m_pGameObject->SetPosition(pos);
	}
}

void BurgerShardComp::Render() const
{
}

void BurgerShardComp::OnCollision(dae::GameObject* other)
{
	//if (other->GetComponent<PeterPepperComp>() == nullptr) return;
	if(!m_SteppedOn)
	{
		m_SteppedOn = true;
		m_BurgerPiece->OnSteppedOn(m_Index);
	}
}



