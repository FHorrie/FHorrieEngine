#pragma once
#include "Component.h"
#include "Subject.h"
#include "GeoStructs.h"

namespace FH
{
	class AttackComponent : public Component, public Subject
	{
	public:
		void DefaultAttack(GameObject* Target);

		void TakeDamage(int damage);

		void GainPoints(bool bigReward);
		
		Rect GetHitBox() const { return m_HitBox; }
		int GetScore() const { return m_Score; }
		int GetLives() const { return m_Lives; }
		bool GetIsDead() const { return m_IsDead; }

		AttackComponent(GameObject* pOwner, Rect hitBox);
		AttackComponent(GameObject* pOwner, Rect hitBox, int lives);
		virtual ~AttackComponent() = default;
		AttackComponent(const AttackComponent& other) = delete;
		AttackComponent(AttackComponent&& other) = delete;
		AttackComponent& operator=(const AttackComponent& other) = delete;
		AttackComponent& operator=(AttackComponent&& other) = delete;

	private:
		Rect m_HitBox{};
		int m_Score{};
		int m_Lives{ 3 };
		bool m_IsDead{};
	};
}

