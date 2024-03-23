#pragma once
#include "Event.h"
#include "SubjectComponent.h"

namespace FH
{
	class Observer abstract
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(SubjectComponent* subComp, Event e) = 0;
	};
}



//Observer() = default;
//~Observer() = default;
//Observer(const Observer& other) = default;
//Observer(Observer&& other) = default;
//Observer& operator=(const Observer& other) = default;
//Observer& operator=(Observer&& other) = default;