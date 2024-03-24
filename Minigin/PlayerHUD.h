#pragma once
#include "Component.h"
#include "Observer.h"

#include <array>

namespace FH
{
	class TextComponent;
	class GameObject;
	class Subject;
	class PlayerHUD : public Component, public Observer
	{
	public:
		void Update() override;

		void OnNotify(GameObject* go, GameEvent e) override;

		PlayerHUD(GameObject* pOwner);
		virtual ~PlayerHUD() = default;
		PlayerHUD(const PlayerHUD& other) = delete;
		PlayerHUD(PlayerHUD&& other) = delete;
		PlayerHUD& operator=(const PlayerHUD& other) = delete;
		PlayerHUD& operator=(PlayerHUD&& other) = delete;

	private:
		std::array<TextComponent*, 2> m_pTextComponent;

		int m_Score{};
		int m_Lives{ 3 };
		bool m_NeedsUpdate{};
	};
}


