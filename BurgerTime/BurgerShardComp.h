#pragma once
#include "GameObject.h"
#include "BaseComponent.h"

class BurgerShardComp : public dae::BaseComponent
{
	bool m_SteppedOn = false;
	int m_Index;
	glm::ivec2 m_ParentPos;
public:
	BurgerShardComp() = delete;
	explicit BurgerShardComp(int idx);
	void Start() override;
	void Update() override;
	void Render() const override;
	void OnCollision(dae::GameObject* other) override;
};

