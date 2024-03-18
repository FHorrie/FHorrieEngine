#pragma once
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{
	class Command abstract
	{
	public:
		Command(GameObject* pGameObject)
			: m_pGameObject{ pGameObject }
		{}
		virtual ~Command() = default;
		virtual void Execute() = 0;
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


	//class MoveUp final : public Command
	//{
	//public:
	//	void Execute(GameObject* pGameObject) override;
	//};
	//
	//class MoveDown final : public Command
	//{
	//public:
	//	void Execute(GameObject* pGameObject) override;
	//};
	//
	//class MoveLeft final : public Command
	//{
	//public:
	//	void Execute(GameObject* pGameObject) override;
	//};
	//
	//class MoveRight final : public Command
	//{
	//public:
	//	void Execute(GameObject* pGameObject) override;
	//};
}


