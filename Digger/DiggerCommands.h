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

	class AttackCommand final : public Command
	{
	public:
		AttackCommand(GameObject* pGameObject);
		~AttackCommand() = default;

		void Execute() override;
	
	private:
		PlayerComponent* m_pPlayer{};
	};
}

