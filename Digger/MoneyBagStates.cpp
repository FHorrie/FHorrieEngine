#include "MoneyBagStates.h"
#include "MoneyBagComponent.h"
#include "PlayerComponent.h"
#include "GeoUtils.h"
#include "FHTime.h"

void FH::IdleBagState::Update(MoneyBagComponent* component)
{
	if (component->GetCurrentCol() == component->GetPlayer()->GetCurrentCol() &&
		component->GetCurrentRow() == component->GetPlayer()->GetCurrentRow() &&
		component->GetCurrentRow() == component->GetPlayer()->GetPreviousRow())
	{
		component->SetState(std::make_unique<MovingBagState>(
			component->GetPlayer()->GetPreviousCol(), component));
		return;
	}
	else if (component->GetNextCellDown().m_IsVisited)
	{
		component->SetState(std::make_unique<FallingBagState>());
		return;
	}
}

FH::MovingBagState::MovingBagState(int prevCol, MoneyBagComponent* component)
	: m_PrevPlayerCol{ prevCol }
{
	const int newCol{ component->GetCurrentCol() + (component->GetCurrentCol() - prevCol) };
	component->SetNewCellTarget(newCol, component->GetCurrentRow());
}

void FH::MovingBagState::Update(MoneyBagComponent* component)
{
	if (!component->IsMoving())
		component->SetState(std::make_unique<IdleBagState>());
}

void FH::FallingBagState::Update(MoneyBagComponent* component)
{
	if (m_AccuFallTime < m_FallTime)
	{
		m_AccuFallTime += (float)Time::GetDeltaTime();
		return;
	}

	if (!component->IsMoving())
	{
		auto nextCell{ component->GetNextCellDown() };
		if (nextCell.m_IsVisited)
			component->SetNewCellTarget(component->GetCurrentCol(), component->GetCurrentRow() + 1);
		else
			component->SetState(std::make_unique<ExposedBagState>());
	}

}

void FH::ExposedBagState::Update(MoneyBagComponent* component)
{
	if (component->GetCurrentCol() == component->GetPlayer()->GetCurrentCol() &&
		component->GetCurrentRow() == component->GetPlayer()->GetCurrentRow() &&
		!component->IsPickedUp())
		component->SetPickedUp();

}