#pragma once
#include "BaseComponent.h"
#include "MiniginPCH.h"

namespace dae
{
	class Texture2D;

	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent() = default;
		TextureComponent(const std::string& filename, int width = 0, int height = 0, glm::ivec4 srcRect = {}, glm::ivec2 dstOffset = {});
		void Start() override {};
		void Update() override;
		void Render() const override;
		void SetTexture(const std::string& filename);
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		int m_Width{};
		int m_Height{};
		glm::ivec4 m_SrcRect{};
		glm::ivec2 m_DstOffset{};
		int m_Test{};
	};
}


