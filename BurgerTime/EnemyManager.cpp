#include "EnemyManager.h"

void EnemyManager::AddEnemyToCollection(std::shared_ptr<EnemyComponent> enemy)
{
	m_Enemies.push_back(enemy);
}

void EnemyManager::StopAllEnemies()
{
	for (auto enemy : m_Enemies)
	{
		enemy->Stop();
	}
}

void EnemyManager::ResetAllEnemies()
{
	for (auto enemy : m_Enemies)
	{
		enemy->Reset();
	}
}
