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
		}

		void Update() override;

	private:

	};
}
