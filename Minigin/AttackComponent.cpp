#include "GeoUtils.h"
#include "GameObject.h"
#include "AttackComponent.h"
#include "Subject.h"

using namespace FH;

AttackComponent::AttackComponent(GameObject* pOwner, Rect hitBox)
	: Component(pOwner)
	, m_HitBox(hitBox)
{}

AttackComponent::AttackComponent(GameObject* pOwner, Rect hitBox, int lives)
	: Component(pOwner)
	, m_HitBox(hitBox)
	, m_Lives(lives)
{}

void AttackComponent::GainPoints(bool bigReward)
{
	if (bigReward)
		Notify(GetOwner(), GameEvent::EVENT_INCREASE_SCORE_BIG);
	else
		Notify(GetOwner(), GameEvent::EVENT_INCREASE_SCORE_SMALL);
}

void AttackComponent::DefaultAttack(GameObject* Target)
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

void AttackComponent::TakeDamage(int damage)
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

