#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename, glm::ivec2 position, int width, int height, glm::ivec4 srcRect)
{
	m_Position = position;
	m_SrcRect = srcRect;
	m_Width = width;
	m_Height = height;
	SetTexture(filename);
}

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::Render() const
{
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_Position.x, m_Position.y, m_Width, m_Height, m_SrcRect);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
