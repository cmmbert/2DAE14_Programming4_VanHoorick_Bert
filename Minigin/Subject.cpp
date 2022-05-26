#include "MiniginPCH.h"
#include "Subject.h"

void Subject::RemoveObserver(const Observer* obs)
{
	std::erase(m_pObservers, obs);
}

void Subject::NotifyAllObservers(const dae::GameObject& entity, eEvent event)
{
	for (size_t i = 0; i < m_pObservers.size(); ++i)
	{
		m_pObservers[i]->OnNotify(entity, event);
	}
}
