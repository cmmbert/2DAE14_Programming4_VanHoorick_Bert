#pragma once
#include "TextComponent.h"
namespace dae
{
	class FpsCounterComp final : public TextComponent
	{
	public:
		FpsCounterComp(const std::string& text, const std::shared_ptr<Font>& font)
			: TextComponent(text, font)
		{
			m_Prefix = text;
		}

		void Update(float elapsedSec) override;
		void SetPrefix(const std::string& text) { m_Prefix = text; }
	private:
		std::string m_Prefix{};
	};
}
