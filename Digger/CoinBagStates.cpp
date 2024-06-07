#include "CoinBagStates.h"
#include "CoinBagComponent.h"
#include "PlayerComponent.h"
#include "GridMapComponent.h"
#include "GeoUtils.h"
#include "FHTime.h"
#include "SoundLocator.h"

void FH::IdleBagState::Update(CoinBagComponent* component)
{
	if (component->GetCurrentCell()->m_HasPlayer && 
		component->GetCurrentRow() == component->GetPlayer()->GetPreviousRow())
	{
		component->SetState(std::make_unique<MovingBagState>(
			component->GetPlayer()->GetPreviousCol(), component));
		return;
	}
	else if (component->GetNextCellDown()->m_IsVisited)
	{
		component->SetState(std::make_unique<FallingBagState>(component));
		return;
	}
}

FH::MovingBagState::MovingBagState(int prevCol, CoinBagComponent* component)
	: m_PrevPlayerCol{ prevCol }
{
	const int newCol{ component->GetCurrentCol() + (component->GetCurrentCol() - prevCol) };
	component->SetNewCellTarget(newCol, component->GetCurrentRow());
}

void FH::MovingBagState::Update(CoinBagComponent* component)
{
	component->UpdatePos();

	if (!component->IsMoving())
		component->SetState(std::make_unique<IdleBagState>());
}

FH::FallingBagState::FallingBagState(CoinBagComponent* component)
{
	component->StateNotify(GameEvent::EVENT_BAG_WIGGLE);
	SoundLocator::GetSoundService().Play("BagWiggle", 0.3f);
}

void FH::FallingBagState::Update(CoinBagComponent* component)
{
	if (m_AccuFallTime < m_FallTime)
	{
		m_AccuFallTime += Time::GetDeltaTime();
		return;
	}

	if (!m_Notified)
	{
		component->StateNotify(GameEvent::EVENT_BAG_FALL);
		m_Notified = true;
	}

	component->UpdatePos();

	if (!component->IsMoving())
	{
		auto* nextCell{ component->GetNextCellDown() };
		if (nextCell == nullptr)
		{
			component->SetState(std::make_unique<ExposedBagState>(component));
			return;
		}

		if (nextCell->m_IsVisited)
		{
			SoundLocator::GetSoundService().Play("BagFall", 0.3f);
			component->SetNewCellTarget(component->GetCurrentCol(), component->GetCurrentRow() + 1);
		}
		else
		{
			component->SetState(std::make_unique<ExposedBagState>(component));
		}
	}

}

FH::ExposedBagState::ExposedBagState(CoinBagComponent* component)
{
	component->StateNotify(GameEvent::EVENT_BAG_BREAK);
	SoundLocator::GetSoundService().Play("BagBreak", 0.3f);
	m_pCurrentCell = component->GetCurrentCell();
	m_pCurrentCell->m_HasBag = false;
}

void FH::ExposedBagState::Update(CoinBagComponent* component)
{
	if(m_pCurrentCell->m_HasPlayer)
		component->SetState(std::make_unique<CollectedBagState>(component));
}

FH::CollectedBagState::CollectedBagState(CoinBagComponent* component)
{
	component->GetPlayer()->GainPoints(PointType::CoinType);
	component->StateNotify(GameEvent::EVENT_BAG_PICKUP);
}