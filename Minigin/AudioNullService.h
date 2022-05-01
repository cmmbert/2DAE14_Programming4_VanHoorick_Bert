#pragma once
#include "IAudioService.h"

class AudioNullService final : public IAudioService 
{
	void PlaySound(int SoundID, float volume) override {}
	void StopSound(int SoundID) override {}
	void StopAllSounds() override {}
};

