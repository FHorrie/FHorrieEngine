#pragma once
#include "GameObject.h"
#include "TransformComponent.h"

namespace FH
{
	class Command abstract
	{
	public:
		Command(GameObject* pGameObject)
			: m_pGameObject{ pGameObject }
		{}
		virtual ~Command() = default;
		virtual void Execute() = 0;
	protected:
		GameObject* GetGameObjectPtr() { return m_pGameObject; }
	private:
		GameObject* m_pGameObject;
	};

	class MoveCommand final : public Command
	{
	public:
		MoveCommand(GameObject* pGameObject, const glm::vec3& direction, float movementSpeed);
		~MoveCommand() = default;

		void Execute() override;

	private:
		glm::vec3 m_Direction;

		float m_MovementSpeed;
	};

	class AttackCommand final : public Command
	{
	public:
		AttackCommand(GameObject* pGameObject);
		~AttackCommand() = default;

		void Execute() override;
	};

	class GainScoreCommand final : public Command
	{
	public:
		GainScoreCommand(GameObject* pGameObject, bool IsBig);
		~GainScoreCommand() = default;

		void Execute() override;

	private:
		bool m_BigReward{};
	};
}


