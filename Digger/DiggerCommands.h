#pragma once
#include <glm/vec2.hpp>

#include "Command.h"
#include "PlayerComponent.h"

namespace FH
{
	class GridMapComponent;
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(GameObject* pGameObject, const glm::vec2& direction,
			GridMapComponent* map);
		~MoveCommand() = default;

		void Execute() override;

	private:
		glm::vec2 m_Direction{};
		
		PlayerComponent* m_pPlayer{};

		const int m_MaxCol{};
		const int m_MaxRow{};
	};

	class AcceptCommand final : public Command
	{
	public:
		AcceptCommand(GameObject* pGameObject);
		~AcceptCommand() = default;

		void Execute() override;
	};
}

