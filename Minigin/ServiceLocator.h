#pragma once
#include "AudioNullService.h"
#include "IAudioService.h"

class ServiceLocator
{
public:
	static IAudioService* GetAudioService();
	static void RegisterAudioService(std::shared_ptr<IAudioService> newService);

private:

	static std::shared_ptr<IAudioService> m_pAudioService;
	static AudioNullService m_pAudioNullService;
};

