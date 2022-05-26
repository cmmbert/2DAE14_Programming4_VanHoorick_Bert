#pragma once
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Scene.h"
#include "TextureComponent.h"

class BurgerPiece : public dae::BaseComponent
{
	std::vector<std::shared_ptr<dae::GameObject>> m_pShards{};
	int m_ShardSize;

public:
	BurgerPiece(dae::GameObject* gameObject, int shardSize = 80);
	void GenerateShards(glm::ivec2 texSrc, dae::Scene& sceneRef);
	void Start() override;
	void Update() override;
	void Render() const override;
};

