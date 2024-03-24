#pragma once
#include "Component.h"
#include "Observer.h"

class CSteamAchievements;

namespace FH
{
	class SteamAchievementComponent : public Component, public Observer
	{
	public:
		void OnNotify(GameObject* go, GameEvent e) override;

		SteamAchievementComponent(GameObject* pOwner, CSteamAchievements* steamAch);
		virtual ~SteamAchievementComponent() = default;
		SteamAchievementComponent(const SteamAchievementComponent& other) = delete;
		SteamAchievementComponent(SteamAchievementComponent&& other) = delete;
		SteamAchievementComponent& operator=(const SteamAchievementComponent& other) = delete;
		SteamAchievementComponent& operator=(SteamAchievementComponent&& other) = delete;
	
	private:
		CSteamAchievements* m_SteamAch;
	};
}

