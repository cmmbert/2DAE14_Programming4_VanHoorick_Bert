#include "MiniginPCH.h"
#include "ServiceLocator.h"

IAudioService* ServiceLocator::GetAudioService()
{
    return GetInstance().m_pAudioService;
}

void ServiceLocator::RegisterAudioService(IAudioService* newService)
{
    if(GetInstance().m_pAudioService != nullptr)
    {
        delete GetInstance().m_pAudioService;
        GetInstance().m_pAudioService = nullptr;
    }
    if (newService == nullptr)
    {
        // Revert to null service.
        GetInstance().m_pAudioService = &GetInstance().m_pAudioNullService;
    }
    else
    {
        GetInstance().m_pAudioService = newService;
    }
}

ServiceLocator::~ServiceLocator()
{
    if (GetInstance().m_pAudioService != nullptr)
    {
        delete GetInstance().m_pAudioService;
        GetInstance().m_pAudioService = nullptr;
    }
}
