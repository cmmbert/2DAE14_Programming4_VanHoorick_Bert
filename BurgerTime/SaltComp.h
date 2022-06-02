#pragma once
#include <BaseComponent.h>

#include "Scene.h"

class SaltComp final :
    public dae::BaseComponent
{
	float m_TimeAlive{};
	float m_TTL{ 0.5f };
	dae::Scene& m_SceneRef;
public:
	explicit SaltComp(dae::GameObject* gameObject, dae::Scene& scene)
		: BaseComponent(gameObject), m_SceneRef(scene)
	{
	}

	void Update() override;
	void Reset();
};

