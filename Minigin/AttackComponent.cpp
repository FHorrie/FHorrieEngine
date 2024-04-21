#include "GeoUtils.h"
#include "GameObject.h"
#include "AttackComponent.h"
#include "Subject.h"

FH::AttackComponent::AttackComponent(GameObject* pOwner, Rect hitBox)
	: Component(pOwner)
	, m_HitBox(hitBox)
{}

FH::AttackComponent::AttackComponent(GameObject* pOwner, Rect hitBox, int lives)
	: Component(pOwner)
	, m_HitBox(hitBox)
	, m_Lives(lives)
{}

void FH::AttackComponent::GainPoints(bool bigReward)
{
	if (bigReward)
		m_Score += 100;
	else
		m_Score += 10;
	Notify(GetOwner(), GameEvent::EVENT_INCREASE_SCORE);

	if (m_Score >= 500)
		Notify(GetOwner(), GameEvent::EVENT_SCORE_500);
}

void FH::AttackComponent::DefaultAttack(GameObject* Target)
{
	if (!m_IsDead)
	{
		auto targetAttackComp = Target->GetComponentOfType<AttackComponent>();

		if (utils::IsOverlapping(m_HitBox, targetAttackComp->GetHitBox()))
		{
			targetAttackComp->TakeDamage(1);
		}
	}
}

void FH::AttackComponent::TakeDamage(int damage)
{
	if (!m_IsDead)
	{
		m_Lives -= damage;

		if (m_Lives <= 0)
		{
			m_Lives = 0;
			m_IsDead = true;
			Notify(GetOwner(), GameEvent::EVENT_ACTOR_HIT);
		}
	}
}

