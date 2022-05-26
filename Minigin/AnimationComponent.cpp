#include "MiniginPCH.h"
#include "AnimationComponent.h"
#include "GlobalTime.h"

AnimationComponent::AnimationComponent(dae::GameObject* gameObject, std::shared_ptr<dae::TextureComponent> textureComp, float timeBetweenFrames)
: BaseComponent(gameObject), m_TimeBetweenFrames(timeBetweenFrames), m_TextureComp(textureComp)
{
}

void AnimationComponent::AddAnimationFrame(const std::string& animName, glm::ivec2 texCoords)
{
	m_Animations[animName].push_back(texCoords);
}

void AnimationComponent::SetCurrentAnimation(const std::string& animName)
{
	m_CurrentAnimation = animName;
	m_CurrentFrame = 0;
	m_TimeSinceLastFrame = 0;
}

void AnimationComponent::SetAnimationSpeed(float timeBetweenFrames)
{
	m_TimeBetweenFrames = timeBetweenFrames;
}


void AnimationComponent::Update()
{
	m_TimeSinceLastFrame += GlobalTime::GetInstance().GetElapsed();
	if(m_TimeSinceLastFrame > m_TimeBetweenFrames)
	{
		++m_CurrentFrame;
		m_CurrentFrame %= m_Animations[m_CurrentAnimation].size();
		m_TimeSinceLastFrame = 0;
		m_TextureComp->SetSrcRect({ m_Animations[m_CurrentAnimation][m_CurrentFrame], 16,16 });
	}
}

