#pragma once
#pragma once
#include <vector>
#include <string>

#include "Component.h"
#include "Observer.h"

namespace FH
{
	class TextureComponent;
	class PlayerComponent;
	class LivesComponent : public Component, public Observer
	{
	public:
		LivesComponent(GameObject* pOwner, PlayerComponent* pPlayer);
		virtual ~LivesComponent() = default;
		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;

		void OnNotify(GameObject* go, GameEvent e) override;


	private:
		static constexpr int MARGIN{ 3 };

		static constexpr int OFFSET{ 70 };
		static constexpr int DIGGERSIZE{ 18 };
		static constexpr int LIVESAMT{ 3 };

		TextureComponent* m_LivesTexArr[LIVESAMT];

		PlayerComponent* m_pPlayer{};
	};
}


