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
		LevelSettings::GameMode = GameMode::Coop;

	}
};
