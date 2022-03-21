#pragma once
#include "Observer.h"

class Subject
{
public:
	template<typename T>
	void AddObserver(const T& obs) { m_pObservers.push_back(std::make_unique<T>(obs)); }
	template<typename T>
	void RemoveObserver(const T& obs) { std::erase(m_pObservers, obs); }

	void NotifyAllObservers(const dae::GameObject& entity, eEvent event);
private:
	std::vector<std::unique_ptr<Observer>> m_pObservers;
};

