#pragma once
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "BurgerShardComp.h"
#include "LevelSettings.h"
#include "Scene.h"
#include "TextureComponent.h"

class BurgerPiece : public dae::BaseComponent
{
	std::vector<std::shared_ptr<BurgerShardComp>> m_pShards{};
	int m_ShardSize;
	bool m_ShardsSteppedOn[4]{};
	bool m_IsFalling{};
	float m_FallingSpeed{ 100 };
public:
	BurgerPiece(dae::GameObject* gameObject, int shardSize = 8*LevelSettings::Scale);
	void GenerateShards(glm::ivec2 texSrc, dae::Scene& sceneRef);
	void OnSteppedOn(int shardIdx);
	void Start() override;
	void Update() override;
	void Render() const override;
	void FallDown();
};

