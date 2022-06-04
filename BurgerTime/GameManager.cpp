#include "GameManager.h"

#include "EnemyManager.h"
#include "GameObject.h"

void GameManager::RegisterPlayer(std::shared_ptr<dae::GameObject> go, glm::ivec2 spawnPoint)
{
	m_Players.push_back(go);
	m_Spawnpoints.push_back(spawnPoint);
}

void GameManager::Reset()
{
	EnemyManager::GetInstance().ResetAllEnemies();
	for (int i = 0; i < m_Players.size(); ++i)
	{
		m_Players[i]->SetPosition(m_Spawnpoints[i]);
		if(auto pepComp = m_Players[i]->GetComponent<PeterPepperComp>())
		{
			pepComp->Reset();
		}
	}
}

void GameManager::PlayerDied()
{
	EnemyManager::GetInstance().StopAllEnemies();

}


