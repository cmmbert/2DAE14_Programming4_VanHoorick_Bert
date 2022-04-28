#pragma once
#include "IAudioService.h"

class AudioNullService final : public IAudioService 
{
	void PlaySound(int SoundID) override {}
	void StopSound(int SoundID) override {}
	void StopAllSounds() override {}
	~AudioNullService() override {};
};

