#include "MiniginPCH.h"
#include "GlobalTime.h"

void GlobalTime::Update(float elapsedSec)
{
	m_ElapsedSec = elapsedSec;
	m_TotalElapsedSec += elapsedSec;
}
