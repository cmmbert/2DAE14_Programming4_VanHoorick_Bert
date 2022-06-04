#include "MiniginPCH.h"
#include "PlayerObserver.h"

#include "GameObject.h"
#include "PeterPepperComp.h"

void PlayerObserver::OnNotify(const dae::GameObject& entity, eEvent event)
{
	switch (event) {
	case eEvent::PepperDied:
		{
			std::cout << "observed\n";
			PeterPepperComp* pepperComp = entity.GetComponent<PeterPepperComp>();
			//if (pepperComp->m_LivesLeft <= 0) { std::cout << "Game Over\n"; }
			break;
		}

		default: 
			break;
	}
}
