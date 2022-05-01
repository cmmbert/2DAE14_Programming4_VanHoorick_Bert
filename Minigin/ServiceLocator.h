#pragma once
#include "AudioNullService.h"
#include "IAudioService.h"
#include "Singleton.h"

class ServiceLocator
{
public:
	static IAudioService* GetAudioService();
	static void RegisterAudioService(IAudioService* newService);

private:

	static std::shared_ptr<IAudioService> m_pAudioService;
	static AudioNullService m_pAudioNullService;
};

