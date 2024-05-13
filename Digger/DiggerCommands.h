#pragma once
#include "Command.h"
#include "PlayerComponent.h"

namespace FH
{
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(GameObject* pGameObject, const glm::vec2& direction, float movementSpeed);
		~MoveCommand() = default;

		void Execute() override;

	private:
		glm::vec2 m_Direction{};
		
		PlayerComponent* m_pPlayer{};
		float m_MovementSpeed{};
	};

	class AcceptCommand final : public Command
	{
	public:
		AcceptCommand(GameObject* pGameObject);
		~AcceptCommand() = default;

		void Execute() override;
	};
}

