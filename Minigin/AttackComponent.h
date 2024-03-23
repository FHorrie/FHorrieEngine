#pragma once
#include "Component.h"

namespace FH
{
	class AttackComponent : public Component
	{
	public:
		void DefaultAttack();

		AttackComponent(GameObject* pOwner);
		virtual ~AttackComponent() = default;
		AttackComponent(const AttackComponent& other) = delete;
		AttackComponent(AttackComponent&& other) = delete;
		AttackComponent& operator=(const AttackComponent& other) = delete;
		AttackComponent& operator=(AttackComponent&& other) = delete;

	private:

	};
}

