#include "MiniginPCH.h"
#include "Subject.h"

void Subject::NotifyAllObservers(const dae::GameObject& entity, eEvent event)
{
	for (int i = 0; i < m_pObservers.size(); ++i)
	{
		m_pObservers[i]->OnNotify(entity, event);
	}
}