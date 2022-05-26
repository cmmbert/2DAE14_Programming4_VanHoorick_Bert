#include "MiniginPCH.h"
#include "PointsComp.h"

PointsComp::PointsComp(dae::GameObject* gameObject, const std::string& prefix)
	: BaseComponent(gameObject),
	m_Prefix(prefix)
{
}
