#include "GameManager.h"

#include "AnimationComponent.h"
#include "EnemyManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureComponent.h"

void GameManager::RegisterPlayer(std::shared_ptr<dae::GameObject> go, glm::ivec2 spawnPoint)
{
	m_Players.push_back(go);
	m_Spawnpoints.push_back(spawnPoint);
}

void GameManager::Reset()
{
	EnemyManager::GetInstance().ResetAllEnemies();
	for (size_t i = 0; i < m_Players.size(); ++i)
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

void GameManager::GameOver()
{
	auto& sceneMan = dae::SceneManager::GetInstance();
	auto& scene = sceneMan.CreateScene("GameOver");
	sceneMan.SetActiveScene(sceneMan.GetCurrentScene().GetName(), false);
	sceneMan.SetActiveScene("GameOver");

	auto gameOver = std::make_shared<dae::GameObject>();
	auto texture = std::make_shared<dae::TextureComponent>(gameOver.get(), "Burgertime/gameOver.png");
	gameOver->AddComponent(texture);
	auto middle = dae::Renderer::GetInstance().ScreenSize()/2;
	auto scale = glm::ivec2{ 480, 336 };
	gameOver->SetSize(scale.x, scale.y);
	gameOver->SetPosition({ middle.x - scale.x / 2, middle.y - scale.y / 2 });
	scene.Add(gameOver);

	auto pepper = std::make_shared<dae::GameObject>();
	scale = glm::ivec2{ 48 * LevelSettings::Scale, 48 * LevelSettings::Scale };
	pepper->SetSize(scale.x, scale.y);
	pepper->SetPosition({ middle.x - scale.x / 2, middle.y + scale.y / 2 });

	texture = std::make_shared<dae::TextureComponent>(pepper.get(), "Burgertime/spritesheet.png", glm::vec4{ 112,16,16,16 });
	pepper->AddComponent(texture);
	auto animComp = std::make_shared<AnimationComponent>(pepper.get(), texture, 0.2f);
	animComp->AddAnimationFrame("death", { 112, 16 });
	animComp->AddAnimationFrame("death", { 128, 16 });
	animComp->SetCurrentAnimation("death");
	pepper->AddComponent(animComp);

	scene.Add(pepper);

}


