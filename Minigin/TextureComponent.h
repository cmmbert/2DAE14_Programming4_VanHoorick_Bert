#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent() = default;
		TextureComponent(const std::string& filename, glm::ivec2 position,int width = 0, int height = 0, glm::ivec4 srcRect = {});
		void Start() override {};
		void Update() override;
		void Render() const override;
		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y) { m_Position = glm::ivec2(x, y); };
		glm::vec2 GetPosition() { return m_Position; }
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		glm::ivec2 m_Position{};
		int m_Width;
		int m_Height;
		glm::ivec4 m_SrcRect{};
	};
}


