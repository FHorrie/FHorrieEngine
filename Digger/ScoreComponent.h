#pragma once
#include <vector>
#include <string>

#include "Component.h"
#include "Observer.h"

namespace FH
{
	class TextureComponent;
	class PlayerComponent;
	class ScoreComponent : public Component, public Observer
	{
	public:
		ScoreComponent(GameObject* pOwner, PlayerComponent* pPlayer);
		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void OnNotify(GameObject* go, GameEvent e) override;


	private:
		static constexpr int MARGIN{3};
		static constexpr int LETTERSIZE{13};
		static constexpr int LETTERAMT{5};

		TextureComponent* m_NumberTexArr[LETTERAMT];

		PlayerComponent* m_pPlayer{};
	};
}

