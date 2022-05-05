#include "MiniginPCH.h"
#include "ServiceLocator.h"

AudioNullService ServiceLocator::m_pAudioNullService{};
std::shared_ptr<IAudioService> ServiceLocator::m_pAudioService{ &m_pAudioNullService };

IAudioService* ServiceLocator::GetAudioService()
{
    return m_pAudioService.get();
}

void ServiceLocator::RegisterAudioService(IAudioService* newService)
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
