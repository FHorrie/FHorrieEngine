#pragma once
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{
	class Command abstract
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(GameObject* pGameObject) = 0;
	};

	class MoveUp final : public Command
	{
	public:
		void Execute(GameObject* pGameObject) override;
	};

	class MoveDown final : public Command
	{
	public:
		void Execute(GameObject* pGameObject) override;
	};

	class MoveLeft final : public Command
	{
	public:
		void Execute(GameObject* pGameObject) override;
	};

	class MoveRight final : public Command
	{
	public:
		void Execute(GameObject* pGameObject) override;
	};
}


