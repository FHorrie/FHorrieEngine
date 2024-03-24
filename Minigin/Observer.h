#pragma once
#include "Event.h"

namespace FH
{
	class GameObject;
	class Observer abstract
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(GameObject* go, GameEvent e) = 0;
	};
}