#pragma once
#include "BoxColliderComp.h"

class BurgerShardComp : public BoxColliderComp
{
public:
	BurgerShardComp() : BoxColliderComp("burgerPiece")
	{
		
	}

	void Start() override;
	void Update() override;
	void Render() const override;
	void OnCollision(Collider* other) override;
};

