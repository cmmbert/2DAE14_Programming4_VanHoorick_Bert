#pragma once
#include <map>
#include <memory>

#include "PeterPepperComp.h"
#include "Singleton.h"

class GameManager : public dae::Singleton<GameManager>
{
	std::vector<std::shared_ptr<dae::GameObject>> m_Players{};
	std::vector<glm::ivec2> m_Spawnpoints{};

public:
	void RegisterPlayer(std::shared_ptr<dae::GameObject> go, glm::ivec2 spawnPoint);
	void Reset();
	void PlayerDied();
	void GameOver();
	void NextLevel();
};

