#pragma once
#include "Observer.h"
#include "TextComponent.h"
#include "PeterPepperComp.h"

class LivesLeftComp final : public dae::TextComponent, public Observer
{
public:
	LivesLeftComp(dae::GameObject* gameObject, const std::string& prefix, const std::shared_ptr<dae::Font>& font)
		: TextComponent(gameObject, prefix, font)
	{
		m_Prefix = prefix;
	}
	
	void Update() override;
	void OnNotify(const dae::GameObject& entity, eEvent event) override
	{
		switch (event) {
		case eEvent::PepperDied:
		{
			std::cout << "observed\n";
			PeterPepperComp* pepperComp = entity.GetComponent<PeterPepperComp>();
			//SetText(m_Prefix + std::to_string(pepperComp->m_LivesLeft));
			break;
		}

		default:
			break;
		}
	}

private:
	std::string m_Prefix{};
};

