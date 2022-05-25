#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename, int width, int height, glm::ivec4 srcRect, glm::ivec2 dstOffset) :
	m_Width(width), m_Height(height), m_SrcRect(srcRect)
{
	m_DstOffset = dstOffset;
	SetTexture(filename);
}

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::Render() const
{
	auto pos = glm::ivec2{ m_pGameObject->GetPosition().x, -m_pGameObject->GetPosition().y };
	pos += m_DstOffset;
	dae::Renderer::GetInstance().RenderTexture(* m_Texture, pos.x, pos.y, m_Width, m_Height, m_SrcRect);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
