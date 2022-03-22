#pragma once
#include "Observer.h"

class Subject
{
public:
	//template<typename T>
	void AddObserver(Observer* obs) { m_pObservers.push_back(obs); }
	template<typename T>
	void RemoveObserver(const T& obs) { std::erase(m_pObservers, obs); }

	void NotifyAllObservers(const dae::GameObject& entity, eEvent event);
private:
	std::vector<Observer*> m_pObservers;
};

