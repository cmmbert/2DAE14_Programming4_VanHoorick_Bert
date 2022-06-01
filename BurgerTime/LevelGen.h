#pragma once
#include <memory>

#include "AnimationComponent.h"
#include "BlockComp.h"
#include "BoxColliderComp.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#define _DEBUGRENDERING 1 //1 for debug collision boxes etc

class LevelGen
{
public:
	static std::shared_ptr<dae::GameObject> GenerateHotdog(glm::ivec2 spawnPoint, std::shared_ptr < dae::GameObject> target);
	static std::shared_ptr<dae::GameObject> GeneratePeter(glm::ivec2 pos);
	static std::shared_ptr<dae::GameObject> GenerateBlockingField(Direction direction);
	static std::shared_ptr<dae::GameObject> GenerateLadder(glm::ivec2 pos, glm::ivec2 scale, dae::Scene& scene);
	static std::shared_ptr<dae::GameObject> GenerateFloorDark(glm::ivec2 pos);
	static std::shared_ptr<dae::GameObject> GenerateFloorLight(glm::ivec2 pos);
	static std::shared_ptr<dae::GameObject> GenerateBurgerPiece(glm::ivec2 pos, glm::ivec2 texCoord, dae::Scene& scene);
	static std::shared_ptr<dae::GameObject> GenerateBurgerTray(glm::ivec2 pos, dae::Scene& scene, int partsNeeded);



};

