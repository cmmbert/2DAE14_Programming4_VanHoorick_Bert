#include "MiniginPCH.h"
#include "LivesLeftComp.h"


void LivesLeftComp::Update()
{
	TextComponent::Update();
}

//void LivesLeftComp::OnNotify(const dae::GameObject& entity, eEvent event)
//{
//	Observer::OnNotify(entity, event);
//	switch (event) {
//	case eEvent::PepperDied:
//	{
//		std::cout << "observed\n";
//		PeterPepperComp* pepperComp = entity.GetComponent<PeterPepperComp>();
//		SetText(m_Prefix + std::to_string(pepperComp->m_LivesLeft));
//		break;
//	}
//
//	default:
//		break;
//	}
//}
