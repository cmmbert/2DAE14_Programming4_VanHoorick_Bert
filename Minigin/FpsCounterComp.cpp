#include "MiniginPCH.h"
#include "FpsCounterComp.h"

void dae::FpsCounterComp::Update(float elapsedSec)
{
	TextComponent::Update(elapsedSec);
	const int fps = static_cast<int>(1.f / elapsedSec);
	SetText(m_Prefix + std::to_string(fps));
}
