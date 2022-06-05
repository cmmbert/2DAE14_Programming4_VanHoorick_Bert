#include "GameManagerHelper.h"
#include "GameManager.h"
#include "GlobalTime.h"

void GameManagerHelper::Update()
{
	if(m_Trigger)
	{
		m_TimeLeftToWait -= GlobalTime::GetInstance().GetElapsed();
		if(m_TimeLeftToWait < 0)
		{
			m_Trigger = false;
			GameManager::GetInstance().OnCollisionsDeleted();
		}
	}
}
