#pragma once
#include "Observer.h"

namespace FH
{
	enum class Achievement
	{
		ACHIEVEMENT_FIRST_BLOOD,
		ACHIEVEMENT_500_SCORE
	};

	class Achievements : public Observer
	{
	public:
		virtual void OnNotify(SubjectComponent* subComp, Event e) override;

	private:
		void Unlock(Achievement achievement);
	};
}

