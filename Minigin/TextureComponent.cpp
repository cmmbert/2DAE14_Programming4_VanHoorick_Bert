#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename, glm::vec2 position)
{
	m_Position = position;
	SetTexture(filename);
}

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::Render() const
{
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_Position.x, m_Position.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
