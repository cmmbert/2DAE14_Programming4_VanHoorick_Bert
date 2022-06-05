#include "BurgerTray.h"

#include "BurgerPiece.h"
#include "GameManager.h"
#include "GameObject.h"

void BurgerTray::OnBurgerAttach()
{
	++m_AmountOfParts;
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x, pos.y + m_BurgerHeight);
	if(m_AmountOfParts == m_AmountOfPartsNeeded)
		GameManager::GetInstance().BurgerCompleted();
}

void BurgerTray::OnCollision(dae::GameObject* other)
{
	if (other->GetComponent<BurgerPiece>())
	{
		m_BurgerHeight = other->GetTransform().GetSize().y +1;
		OnBurgerAttach();
	}
}
