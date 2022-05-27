#include "LadderComp.h"

#include "GameObject.h"
#include "TextureComponent.h"

LadderComp::LadderComp(dae::GameObject* gameObject, dae::Scene& sceneRef): BaseComponent(gameObject), m_SceneRef(sceneRef)
{
	RecalculateSize();
}

void LadderComp::RecalculateSize()
{
	m_NrOfSteps = m_pGameObject->GetTransform().GetSize().y / 2;
	for (auto child : m_pGameObject->GetChildren())
	{
		m_SceneRef.Destroy(child);
	}
	for (int i = 0; i < m_NrOfSteps; ++i)
	{
		auto step = std::make_shared<dae::GameObject>();
		auto texture = std::make_shared<dae::TextureComponent>(step.get(), "Burgertime/spritesheet.png", glm::vec4{ 202,156,16,2 });
		step->AddComponent(texture);
		step->SetPosition(0, i * 20);
		step->SetSize(160, 20);
		m_SceneRef.Add(step);
	}
}
