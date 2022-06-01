#pragma once
#include <BaseComponent.h>
class BurgerTray final :
    public dae::BaseComponent
{

	int m_AmountOfParts{};
	int m_AmountOfPartsNeeded;
	int m_BurgerHeight{};
	void OnBurgerAttach();
public:
	explicit BurgerTray(dae::GameObject* gameObject, int amountOfPartsNeeded)
		: BaseComponent(gameObject), m_AmountOfPartsNeeded(amountOfPartsNeeded)
	{
	}

	void OnCollision(dae::GameObject* other) override;
};

