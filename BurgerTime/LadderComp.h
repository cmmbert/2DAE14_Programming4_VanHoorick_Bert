#pragma once
#include "BaseComponent.h"
#include "Scene.h"

class LadderComp final : public dae::BaseComponent 
{
	int m_NrOfSteps{};
	dae::Scene& m_SceneRef;
public:
	LadderComp() = delete;
	LadderComp(dae::GameObject* gameObject, dae::Scene& sceneRef);

	void RecalculateSize();
	
};

