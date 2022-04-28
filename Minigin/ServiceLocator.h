#pragma once
#include "AudioNullService.h"
#include "IAudioService.h"

class ServiceLocator
{
public:
	static IAudioService* GetAudioService() { return m_pAudioService; }
	static void RegisterAudioService(IAudioService* newService)
	{
        if (newService == nullptr)
        {
            // Revert to null service.
            m_pAudioService = &m_pAudioNullService;
        }
        else
        {
            m_pAudioService = newService;
        }
	}

private:
	static IAudioService* m_pAudioService;
	static AudioNullService m_pAudioNullService;
};

