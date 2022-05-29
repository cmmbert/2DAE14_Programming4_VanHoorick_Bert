#pragma once
#include "BaseComponent.h"
#include "LevelSettings.h"
#include "Scene.h"

class LadderComp final : public dae::BaseComponent 
{
	int m_NrOfSteps{};
	dae::Scene& m_SceneRef;
	const glm::ivec2 m_StepSize{ 16*LevelSettings::Scale, 2*LevelSettings::Scale };
public:
	LadderComp() = delete;
	LadderComp(dae::GameObject* gameObject, dae::Scene& sceneRef);

	void RecalculateSize();
	
};

