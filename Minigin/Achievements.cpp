#include "Achievements.h"

using namespace FH;

void Achievements::OnNotify(SubjectComponent* subComp, Event e)
{
	switch (e)
	{
	case FH::Event::EVENT_ACTOR_DIED:
		subComp->GetSubjectOwner()->GetComponentOfType<>();
		break;
	default:
		break;
	}
}

void Unlock(Achievement achievement)
{

}