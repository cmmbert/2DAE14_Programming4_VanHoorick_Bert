#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent() = default;
		TextureComponent(const std::string& filename, glm::vec2 position);
		void Update(float elapsedSec) override;
		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y) { m_Position = glm::vec2(x, y); };
		glm::vec2 GetPosition() { return m_Position; }
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		glm::vec2 m_Position{};
	};
}


