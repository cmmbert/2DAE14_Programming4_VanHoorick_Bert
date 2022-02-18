#include "MiniginPCH.h"
#include "FpsCounterComp.h"

#include "Time.h"

void dae::FpsCounterComp::Update(float elapsedSec)
{
	TextComponent::Update(elapsedSec);
	const int fps = static_cast<int>(1.f / Time::GetInstance().GetElapsed());
	SetText(m_Prefix + std::to_string(fps));
}
