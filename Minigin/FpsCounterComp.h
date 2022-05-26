#pragma once
#include "TextComponent.h"
namespace dae
{
	class FpsCounterComp final : public TextComponent
	{
	public:
		FpsCounterComp(dae::GameObject* gameObject, const std::string& text, const std::shared_ptr<Font>& font)
			: TextComponent(gameObject, text, font)
		{
			m_Prefix = text;
		}
		
		void Update() override;
		void SetPrefix(const std::string& text) { m_Prefix = text; }
	private:
		std::string m_Prefix{};
	};
}
