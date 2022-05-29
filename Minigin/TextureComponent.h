#pragma once
#include "BaseComponent.h"
#include "MiniginPCH.h"

namespace dae
{
	class Texture2D;

	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent() = delete;
		TextureComponent(dae::GameObject* gameObject, const std::string& filename, glm::ivec4 srcRect = {}, glm::ivec2 dstOffset = {});
		void Render() const override;
		void SetTexture(const std::string& filename);
		glm::ivec4 GetTexCoord() const { return m_SrcRect; }
		void SetSrcRect(glm::ivec4 srcRect);
		bool m_Flipped{};
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		glm::ivec4 m_SrcRect{};
		glm::ivec2 m_DstOffset{};
		int m_Test{};
	};
}


