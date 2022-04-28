#pragma once
#include "IAudioService.h"
class SDLMixerAudioService final :
    public IAudioService
{
	void PlaySound(int soundID) override;
	void StopSound(int soundID) override;
	void StopAllSounds() override;
	~SDLMixerAudioService() override {};
};

