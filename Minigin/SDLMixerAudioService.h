#pragma once
#include "IAudioService.h"
#include "mutex"

class SDLMixerAudioService final :
    public IAudioService
{
	std::mutex m_Mutex;
	bool m_IsLooping = true;
	int m_QHead = 0;
	int m_QTail = 0;
	static const int m_QueueLength = 32;
	Sound m_Queue[m_QueueLength]{};
	bool m_HasItemsQueued = false;
	void ActuallyPlaySound(Sound sound);

	std::thread m_AudioThread{};
public:
	SDLMixerAudioService();
	~SDLMixerAudioService() override;

	void PlaySound(int soundID, float volume) override;
	void StopSound(int soundID) override;
	void StopAllSounds() override;

	//~SDLMixerAudioService() override {};


	void QueueLoop();
	void StopQueue() { m_IsLooping = false; }
	void StartQueue() { m_IsLooping = true; }
};

