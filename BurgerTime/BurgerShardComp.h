#pragma once
#include "GameObject.h"
#include "BaseComponent.h"

class BurgerPiece;

class BurgerShardComp : public dae::BaseComponent
{
	const int m_Nudge{ -m_pGameObject->GetTransform().GetSize().y/2/4 };
	int m_Index;
	int m_OriginalY;
	int m_NudgeMultiplier{1};
	BurgerPiece* m_BurgerPiece;
public:
	BurgerShardComp() = delete;
	explicit BurgerShardComp(dae::GameObject* gameObject, int idx, BurgerPiece* burgerPiece);
	void Start() override;
	void Update() override;
	void Render() const override;
	void OnCollision(dae::GameObject* other) override;
	bool m_SteppedOn = false;
	void Reset();
	void IncrementNudge();
};

