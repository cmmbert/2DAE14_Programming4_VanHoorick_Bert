#pragma once
#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	void Update(float elapsedSec);
	float GetElapsed() const { return m_ElapsedSec; }
	float GetTotal() const { return m_TotalElapsedSec; }
private:
	float m_ElapsedSec{};
	float m_TotalElapsedSec{};
};

