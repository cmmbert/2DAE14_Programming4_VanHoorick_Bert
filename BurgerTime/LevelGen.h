#pragma once
#include <memory>

#include "AnimationComponent.h"
#include "BlockComp.h"
#include "BoxColliderComp.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#define _DEBUGRENDERING 0 //1 for debug collision boxes etc

class LevelGen
{
	static std::shared_ptr<dae::GameObject> GenerateEnemy(glm::ivec2 spawnPoint, std::shared_ptr < dae::GameObject> target);

public:
	static std::shared_ptr<dae::GameObject> GenerateHotdog(glm::ivec2 spawnPoint, std::shared_ptr < dae::GameObject> target);
	static std::shared_ptr<dae::GameObject> GenerateEgg(glm::ivec2 spawnPoint, std::shared_ptr < dae::GameObject> target);
	static std::shared_ptr<dae::GameObject> GeneratePickle(glm::ivec2 spawnPoint, std::shared_ptr < dae::GameObject> target);
	static std::shared_ptr<dae::GameObject> GeneratePeter(glm::ivec2 pos, bool usesKeyboard);
	static std::shared_ptr<dae::GameObject> GeneratePlayerHotdog(glm::ivec2 pos, bool usesKeyboard);
	static std::shared_ptr<dae::GameObject> GenerateBlockingField(Direction direction);
	static std::shared_ptr<dae::GameObject> GenerateLadder(glm::ivec2 pos, glm::ivec2 scale, dae::Scene& scene);
	static std::shared_ptr<dae::GameObject> GenerateFloorDark(glm::ivec2 pos, dae::Scene& scene);
	static std::shared_ptr<dae::GameObject> GenerateFloorLight(glm::ivec2 pos, dae::Scene& scene);
	static std::shared_ptr<dae::GameObject> GenerateBurgerPiece(glm::ivec2 pos, glm::ivec2 texCoord, dae::Scene& scene);
	static std::shared_ptr<dae::GameObject> GenerateBurgerTray(glm::ivec2 pos, dae::Scene& scene, int partsNeeded);

	static void ReadLevelFromFile(const std::string& filePath, dae::Scene& scene);

};

