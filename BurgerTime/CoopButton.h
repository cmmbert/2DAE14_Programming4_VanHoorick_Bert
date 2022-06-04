#pragma once
#include "LevelGen.h"
#include "ModeButton.h"
#include "SceneManager.h"
#include "LevelSettings.h"

class CoopButton :
	public ModeButton
{
public:
	CoopButton(dae::GameObject* gameObject, dae::TextureComponent* texture)
		: ModeButton(gameObject, texture)
	{
	}

	void SetMode() override
	{
		dae::SceneManager::GetInstance().SetActiveScene("Menu", false);
		LevelSettings::GameMode = GameMode::Coop;
		LevelGen::ReadLevelFromFile("BurgerTime/level.json", dae::SceneManager::GetInstance().GetScene("Level1"));

		dae::SceneManager::GetInstance().SetActiveScene("Level1");

	}
};
