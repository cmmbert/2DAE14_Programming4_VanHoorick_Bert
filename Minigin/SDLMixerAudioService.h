#pragma once
#include "IAudioService.h"

class SDLMixerAudioService final :
    public IAudioService
{
public:
	void PlaySound(int soundID, float volume) override;
	void StopSound(int soundID) override;
	void StopAllSounds() override;

	//~SDLMixerAudioService() override {};


	void QueueLoop();
	void StopQueue() { m_IsLooping = false; }
	void StartQueue() { m_IsLooping = true; }
private:
	bool m_IsLooping = true;
	int m_QHead = 0;
	int m_QTail = 0;
	static const int m_QueueLength = 32;
	Sound m_Queue[m_QueueLength]{};
	bool m_HasItemsQueued = false;
	void ActuallyPlaySound(Sound sound);
};

