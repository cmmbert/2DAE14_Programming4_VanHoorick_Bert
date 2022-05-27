#pragma once
#include "GameObject.h"
#include "BaseComponent.h"

class BurgerPiece;

class BurgerShardComp : public dae::BaseComponent
{
	const int m_Nudge{ -20 };
	int m_Index;
	int m_OriginalY;
	BurgerPiece* m_BurgerPiece;
public:
	BurgerShardComp() = delete;
	explicit BurgerShardComp(dae::GameObject* gameObject, int idx, BurgerPiece* burgerPiece);
	void Start() override;
	void Update() override;
	void Render() const override;
	void OnCollision(dae::GameObject* other) override;
	bool m_SteppedOn = false;
};

