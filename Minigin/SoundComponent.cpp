#include "MiniginPCH.h"
#include "SoundComponent.h"

#include "ServiceLocator.h"

void SoundComponent::Play()
{
	ServiceLocator::GetInstance().GetAudioService()->PlaySound(m_SoundId, 0.5f);
}
