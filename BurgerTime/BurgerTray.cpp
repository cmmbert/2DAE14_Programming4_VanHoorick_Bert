#include "BurgerTray.h"

#include "BurgerPiece.h"
#include "GameObject.h"

void BurgerTray::OnBurgerAttach()
{
	++m_AmountOfParts;
	auto pos = m_pGameObject->GetPosition();
	m_pGameObject->SetPosition(pos.x, pos.y + m_BurgerHeight);
}

void BurgerTray::OnCollision(dae::GameObject* other)
{
	if (other->GetComponent<BurgerPiece>())
	{
		m_BurgerHeight = other->GetTransform().GetSize().y +1;
		OnBurgerAttach();
	}
}
