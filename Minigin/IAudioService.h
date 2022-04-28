#pragma once
class IAudioService
{
public:
	virtual ~IAudioService() = default;
	virtual void PlaySound(int soundID) = 0;
	virtual void StopSound(int soundID) = 0;
	virtual void StopAllSounds() = 0;
};

