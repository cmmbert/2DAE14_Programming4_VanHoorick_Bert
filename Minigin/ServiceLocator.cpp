#include "MiniginPCH.h"
#include "ServiceLocator.h"

AudioNullService ServiceLocator::m_pAudioNullService{};
std::shared_ptr<IAudioService> ServiceLocator::m_pAudioService{ std::make_shared<AudioNullService>(m_pAudioNullService) };

IAudioService* ServiceLocator::GetAudioService()
{
    return m_pAudioService.get();
}

void ServiceLocator::RegisterAudioService(std::shared_ptr<IAudioService> newService)
{
    if (newService == nullptr)
    {
        // Revert to null service.
        m_pAudioService = std::shared_ptr<IAudioService>(&m_pAudioNullService);
    }
    else
    {
        m_pAudioService = std::shared_ptr<IAudioService>(newService);
    }
}
