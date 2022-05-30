#include "LadderComp.h"

#include "BoxColliderComp.h"
#include "GameObject.h"
#include "LadderTop.h"
#include "TextureComponent.h"

LadderComp::LadderComp(dae::GameObject* gameObject, dae::Scene& sceneRef): BaseComponent(gameObject), m_SceneRef(sceneRef)
{
	RecalculateSize();
}

void LadderComp::RecalculateSize()
{
	m_NrOfSteps = m_pGameObject->GetTransform().GetSize().y / m_StepSize.y;
	for (auto child : m_pGameObject->GetChildren())
	{
		m_SceneRef.Destroy(child);
	}
	for (int i = 0; i < m_NrOfSteps; ++i)
	{
		auto step = std::make_shared<dae::GameObject>();
		auto texture = std::make_shared<dae::TextureComponent>(step.get(), "Burgertime/spritesheet.png", glm::vec4{ 202,156,16,2 });
		step->SetParent(m_pGameObject);
		step->SetPosition(0, i * m_StepSize.y);
		step->AddComponent(texture);
		step->SetSize(m_StepSize.x, m_StepSize.y);
		m_SceneRef.Add(step);
	}
	//Top step
	auto top = std::make_shared<dae::GameObject>();

	top->SetParent(m_pGameObject);
	top->SetPosition(0, (float)(m_NrOfSteps * m_StepSize.y));
	top->SetSize(m_StepSize.x, m_StepSize.y);

#if _DEBUGRENDERING
	auto texture = std::make_shared<dae::TextureComponent>(top.get(), "Burgertime/spritesheet.png", glm::vec4{ 81,70,1,1 });
	top->AddComponent(texture);
#endif

	auto topStep = std::make_shared<LadderTop>(top.get());
	top->AddComponent(topStep);

	auto coll = std::make_shared<BoxColliderComp>(top.get(), "ladder");
	top->AddComponent(coll);
	m_SceneRef.Add(top);

}

