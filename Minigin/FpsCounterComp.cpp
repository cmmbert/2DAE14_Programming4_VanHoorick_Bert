#include "MiniginPCH.h"
#include "FpsCounterComp.h"

#include "GlobalTime.h"

void dae::FpsCounterComp::Update()
{
	TextComponent::Update();
	const int fps = static_cast<int>(1.f / GlobalTime::GetInstance().GetElapsed());
	SetText(m_Prefix + std::to_string(fps));
}
