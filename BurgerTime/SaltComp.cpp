#include "SaltComp.h"

#include "GameObject.h"
#include "GlobalTime.h"

void SaltComp::Update()
{
	m_TimeAlive += GlobalTime::GetInstance().GetElapsed();
	if(m_TimeAlive > m_TTL)
	{
		m_pGameObject->SetPosition({ -1000,-1000 });
	}
}

void SaltComp::Reset()
{
	m_TimeAlive = 0;
}
