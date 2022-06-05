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
		LevelSettings::GameMode = GameMode::Versus;
	}
};

