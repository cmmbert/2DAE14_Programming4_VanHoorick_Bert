#pragma once
#include "AudioNullService.h"
#include "IAudioService.h"
#include "Singleton.h"

class ServiceLocator : public dae::Singleton<ServiceLocator>
{
public:
	static IAudioService* GetAudioService();
	static void RegisterAudioService(IAudioService* newService);
	~ServiceLocator() override{};

private:
	friend class Singleton<ServiceLocator>;
	ServiceLocator() = default;
	IAudioService* m_pAudioService{};
	AudioNullService m_pAudioNullService{};
};

