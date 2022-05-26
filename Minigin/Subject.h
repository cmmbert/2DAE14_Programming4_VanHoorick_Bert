#pragma once
//#include "MiniginPCH.h"
#include "Observer.h"
#include <vector>

class Subject
{
public:
	void AddObserver(Observer* obs) { m_pObservers.push_back(obs); }
	void RemoveObserver(const Observer* obs);

	void NotifyAllObservers(const dae::GameObject& entity, eEvent event);
private:
	std::vector<Observer*> m_pObservers{};
};

