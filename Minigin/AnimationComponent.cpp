#include "MiniginPCH.h"
#include "AnimationComponent.h"
#include "GlobalTime.h"

AnimationComponent::AnimationComponent(dae::GameObject* gameObject, std::shared_ptr<dae::TextureComponent> textureComp, float timeBetweenFrames)
: BaseComponent(gameObject), m_TimeBetweenFrames(timeBetweenFrames), m_TextureComp(textureComp), m_OriginalTexture(textureComp->GetTexCoord())
{
}

void AnimationComponent::AddAnimationFrame(const std::string& animName, glm::ivec2 texCoords)
{
	m_Animations[animName].push_back(texCoords);
}

void AnimationComponent::SetCurrentAnimation(const std::string& animName)
{
	if (m_CurrentAnimation == animName) return;
	m_Paused = false;
	m_CurrentAnimation = animName;
	m_CurrentFrame = m_Animations[m_CurrentAnimation].size()-1;
	m_TimeSinceLastFrame = 1000;
}

void AnimationComponent::SetAnimationSpeed(float timeBetweenFrames)
{
	m_TimeBetweenFrames = timeBetweenFrames;
}

void AnimationComponent::ContinueAnimation()
{
	m_Paused = false;
}

void AnimationComponent::StopAnimation()
{
	m_TextureComp->SetSrcRect(m_OriginalTexture);
	m_Paused = true;
}


void AnimationComponent::Update()
{
	if (!m_Paused)
	{
		m_TimeSinceLastFrame += GlobalTime::GetInstance().GetElapsed();
		if (m_TimeSinceLastFrame > m_TimeBetweenFrames)
		{
			++m_CurrentFrame;
			m_CurrentFrame %= m_Animations[m_CurrentAnimation].size();
			m_TimeSinceLastFrame = 0;
			m_TextureComp->SetSrcRect({ m_Animations[m_CurrentAnimation][m_CurrentFrame], m_OriginalTexture.b,m_OriginalTexture.a });
		}
	}
}

void AnimationComponent::Reset()
{
	m_CurrentFrame = m_Animations[m_CurrentAnimation].size();
	m_TimeSinceLastFrame = 10000;
}

