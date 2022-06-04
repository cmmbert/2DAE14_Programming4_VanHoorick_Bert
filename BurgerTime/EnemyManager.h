#pragma once
#include <BaseComponent.h>
#include <memory>
#include <vector>

#include "EnemyComponent.h"
#include "Singleton.h"

class EnemyManager :    public dae::Singleton<EnemyManager>
{
private:
    std::vector<std::shared_ptr<EnemyComponent>> m_Enemies{};

public:
    void AddEnemyToCollection(std::shared_ptr<EnemyComponent> enemy);
    void StopAllEnemies();
    void ResetAllEnemies();
    
};

