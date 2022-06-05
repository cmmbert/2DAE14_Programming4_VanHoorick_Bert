#pragma once
#include <map>
#include <memory>

#include "GameManagerHelper.h"
#include "PeterPepperComp.h"
#include "Singleton.h"

class GameManager final : public dae::Singleton<GameManager>
{
	std::vector<std::shared_ptr<dae::GameObject>> m_Players{};
	std::vector<glm::ivec2> m_Spawnpoints{};
	size_t m_BurgersCompleted{};
	std::shared_ptr<GameManagerHelper> m_Helper{};
public:
	void SetHelper(std::shared_ptr<GameManagerHelper> helper) { m_Helper = helper; }
	void RegisterPlayer(std::shared_ptr<dae::GameObject> go, glm::ivec2 spawnPoint);
	void Reset();
	void PlayerDied();
	void GameOver();
	void NextLevel();
	void OnCollisionsDeleted();
	void BurgerCompleted();
};

