#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"

class PointsComp : public dae::BaseComponent, public Observer
{
public:
	PointsComp(dae::GameObject* gameObject, const std::string& prefix);
	~PointsComp() = default;
	PointsComp(const PointsComp& other) = delete;
	PointsComp(PointsComp&& other) noexcept = delete;
	PointsComp& operator=(const PointsComp& other) = delete;
	PointsComp& operator=(PointsComp&& other) noexcept = delete;
	void OnNotify(const dae::GameObject& entity, eEvent event) override
	{
		switch (event) {
		case eEvent::EnemyDied:
		{
			std::cout << "observed\n";
			m_Points += 100;
			dae::TextComponent* textComp = m_pGameObject->GetComponent<dae::TextComponent>();
			textComp->SetText(m_Prefix + std::to_string(m_Points));
			break;
		}

		default:
			break;
		}
	}
private:
	std::string m_Prefix{};
	int m_Points{ 0 };
};


