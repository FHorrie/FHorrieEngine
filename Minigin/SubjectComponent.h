#pragma once
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

	protected:
		void Notify(Event e);

	private:
		std::vector<Observer*> m_pObservers{};
	};

	class SubjectComponent : public Component, Subject
	{
	public:
		SubjectComponent(GameObject* pOwner);
		~SubjectComponent() = default;

		GameObject* GetSubjectOwner() { return GetOwner(); }
	};
}
