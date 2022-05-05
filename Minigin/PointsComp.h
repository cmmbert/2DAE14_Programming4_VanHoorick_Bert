#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"

class PointsComp : public dae::BaseComponent, public Observer
{
public:
	PointsComp(const std::string& prefix) { m_Prefix = prefix; }
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

	void Start() override {};
	void Update() override;
	void Render() const override;
private:
	std::string m_Prefix{};
	int m_Points{ 0 };
};


