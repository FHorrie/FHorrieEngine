#define _CRT_SECURE_NO_WARNINGS
#include "SteamAchievementComponent.h"
#include "SteamAchievements.h"

FH::SteamAchievementComponent::SteamAchievementComponent(GameObject* pOwner, CSteamAchievements* steamAch)
	: Component(pOwner)
	, m_SteamAch(steamAch)
{}

void FH::SteamAchievementComponent::OnNotify(GameObject*, GameEvent e)
{
	switch (e)
	{
	case FH::GameEvent::EVENT_INCREASE_SCORE:
		break;
	case FH::GameEvent::EVENT_SCORE_500:
		if (m_SteamAch)
		{
			m_SteamAch->SetAchievement("ACH_WIN_ONE_GAME");
		}
		break;
	case FH::GameEvent::EVENT_ACTOR_HIT:
		break;
	case FH::GameEvent::EVENT_ACTOR_KILLED:
		break;
	default:
		break;
	}
}