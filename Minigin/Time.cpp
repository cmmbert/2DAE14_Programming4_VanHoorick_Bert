#include "MiniginPCH.h"
#include "Time.h"

void Time::Update(float elapsedSec)
{
	m_ElapsedSec = elapsedSec;
	m_TotalElapsedSec += elapsedSec;
}
