#pragma once
#include <BaseComponent.h>

#include "TextureComponent.h"

class ModeButton :
    public dae::BaseComponent
{
	bool m_IsActive = false;
	dae::TextureComponent* m_Texture;
public:
	explicit ModeButton(dae::GameObject* gameObject, dae::TextureComponent* texture)
		: BaseComponent(gameObject), m_Texture(texture)
	{
	}

    virtual void SetMode() = 0;
	void SetActive(bool active)
	{
		if (active == m_IsActive) return;
		auto pos = m_Texture->GetTexCoord();
		if(active)
		{
			pos.y += 29;
		}
		else
		{
			pos.y -= 29;
		}
		m_Texture->SetSrcRect(pos);
		m_IsActive = active;
	}
};

