#include "MiniginPCH.h"
#include "SDLMixerAudioService.h"
#include "SDL_mixer.h"

void SDLMixerAudioService::PlaySound(int soundID, float volume)
{
	//Technically this method should be called EnqueueSound but to keep the inheritance clean we'll leave it like this
	m_Mutex.lock();
	assert((m_QTail + 1) % m_QueueLength != m_QHead);

	m_Queue[m_QTail] = Sound(soundID, volume);
	m_QTail = (m_QTail + 1) % m_QueueLength;
	m_HasItemsQueued = true;
	m_Mutex.unlock();
}

void SDLMixerAudioService::StopSound(int soundID)
{
}

void SDLMixerAudioService::StopAllSounds()
{
}

void SDLMixerAudioService::QueueLoop()
{
	while(m_IsLooping)
	{
		if (m_HasItemsQueued)
		{
			m_Mutex.lock();
			auto v = m_Queue[m_QHead];
			++m_QHead;
			if (m_QHead == m_QTail) m_HasItemsQueued = false;
			m_Mutex.unlock();
			ActuallyPlaySound(v);
		}
		else
		{
			Sleep(5);
		}
	}
}

void SDLMixerAudioService::ActuallyPlaySound(Sound sound)
{
	std::string output = "Play sound with ID: " + std::to_string(sound.id) + "\n";
	std::cout << output;

	auto sample = Mix_LoadWAV(("../Data/Sounds/" + std::to_string(sound.id) + ".wav").c_str());
	sample->volume = UINT8(sound.volume * 128);
	Mix_PlayChannel(-1, sample, 0);
}
