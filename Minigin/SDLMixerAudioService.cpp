#include "MiniginPCH.h"
#include "SDLMixerAudioService.h"

void SDLMixerAudioService::PlaySound(int soundID, float volume)
{
	//Technically this method should be called EnqueueSound but to keep the inheritance clean we'll leave it like this

	assert((m_QTail + 1) % m_QueueLength != m_QHead);

	m_Queue[m_QTail] = Sound(soundID, volume);
	m_QTail = (m_QTail + 1) % m_QueueLength;
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
		if (m_QHead == m_QTail)
		{
			Sleep(5);
			continue;
		}
		ActuallyPlaySound(m_Queue[m_QHead]);
		++m_QHead;
	}
}

void SDLMixerAudioService::ActuallyPlaySound(Sound sound)
{
	std::string output = "Play sound with ID: " + std::to_string(sound.id) + "\n";
	std::cout << output;

}
