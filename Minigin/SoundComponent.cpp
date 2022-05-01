#include "MiniginPCH.h"
#include "SoundComponent.h"

#include "ServiceLocator.h"

void SoundComponent::Play(float volumePerc)
{
	ServiceLocator::GetAudioService()->PlaySound(m_SoundId, volumePerc);
}
