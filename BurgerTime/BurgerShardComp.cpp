#include "BurgerShardComp.h"


class PeterPepperComp;

BurgerShardComp::BurgerShardComp(int idx) : m_Index(idx)
{
	m_ParentPos = m_pGameObject->GetParent()->GetPosition();
}

void BurgerShardComp::Start()
{
}

void BurgerShardComp::Update()
{
}

void BurgerShardComp::Render() const
{
}

void BurgerShardComp::OnCollision(dae::GameObject* other)
{
	//if (other->GetComponent<PeterPepperComp>() == nullptr) return;
	m_SteppedOn = true;
}



