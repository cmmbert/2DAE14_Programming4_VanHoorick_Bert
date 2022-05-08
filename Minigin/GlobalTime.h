#pragma once
#include "Singleton.h"

class GlobalTime final : public dae::Singleton<GlobalTime>
{
public:
	void Update(float elapsedSec);
	float GetElapsed() const { return m_ElapsedSec; }
	float GetTotal() const { return m_TotalElapsedSec; }
private:
	float m_ElapsedSec{};
	float m_TotalElapsedSec{};
};

