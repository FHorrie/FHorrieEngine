#pragma once
#include <vector>

#include "GameObject.h"
#include "Component.h"
#include "Event.h"

namespace FH
{
	class Observer;
	class Subject
	{
	public:
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);

		Subject() = default;
		~Subject() = default;

	protected:
		void Notify(GameObject* go, GameEvent e);

	private:
		std::vector<Observer*> m_pObservers{};
	};
}
