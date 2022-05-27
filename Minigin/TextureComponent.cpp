#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(dae::GameObject* gameObject, const std::string& filename, glm::ivec4 srcRect, glm::ivec2 dstOffset) : BaseComponent(gameObject),
 m_SrcRect(srcRect)
{
	m_DstOffset = dstOffset;
	SetTexture(filename);
}
void dae::TextureComponent::Render() const
{
	auto pos = glm::ivec2{ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y };
	pos += m_DstOffset;
	dae::Renderer::GetInstance().RenderTexture(* m_Texture, pos.x, pos.y,
		m_pGameObject->GetTransform().GetSize().x, m_pGameObject->GetTransform().GetSize().y, m_SrcRect, m_Flipped);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetSrcRect(glm::ivec4 srcRect)
{
	m_SrcRect = srcRect;
}
