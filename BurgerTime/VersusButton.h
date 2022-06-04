#pragma once
#include "LevelGen.h"
#include "ModeButton.h"
#include "SceneManager.h"

class VersusButton: public ModeButton 
{
public:
	VersusButton(dae::GameObject* gameObject, dae::TextureComponent* texture)
		: ModeButton(gameObject, texture)
	{
	}

	void SetMode() override
	{
		dae::SceneManager::GetInstance().SetActiveScene("Menu", false);
		LevelSettings::GameMode = GameMode::Versus;
		LevelGen::ReadLevelFromFile("BurgerTime/level.json", dae::SceneManager::GetInstance().GetScene("Level1"));

		dae::SceneManager::GetInstance().SetActiveScene("Level1");
	}
};

