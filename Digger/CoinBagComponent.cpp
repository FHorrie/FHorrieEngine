#include "CoinBagComponent.h"
#include "GeoUtils.h"
#include "GridMapComponent.h"
#include "GameObject.h"
#include "Subject.h"
#include "Renderer.h"
#include "PlayerComponent.h"
#include "FHTime.h"

FH::CoinBagComponent::CoinBagComponent(GameObject* pOwner, int col, int row,
	GridMapComponent* pGridMap, PlayerComponent* pPlayer)
	: Component{ pOwner }
	, m_CurrentCol{ col }
	, m_CurrentRow{ row }
	, m_pGridMap{ pGridMap }
	, m_pPlayer{ pPlayer }
{
	if (col < 0 || col > m_pGridMap->GetAmtCols() - 1)
		throw std::exception("col out of range");
	if (row < 0 || row > m_pGridMap->GetAmtRows() - 1)
		throw std::exception("row out of range");

	GetCurrentCell()->m_HasBag = true;

	const auto cellPos{ GetCurrentCell()->m_Center };

	m_PreviousPos = cellPos;
	m_CurrentPos = cellPos;
	m_DesiredPos = cellPos;


	const glm::vec2 bagPos{ cellPos.x - m_HitBox.m_Width / 2,  cellPos.y - m_HitBox.m_Height / 2 };

	m_HitBox.m_Left = bagPos.x;
	m_HitBox.m_Bottom = bagPos.y;

	pOwner->SetLocalPosition({ bagPos, 0 });
}

void FH::CoinBagComponent::Update()
{
	m_State->Update(this);
}

void FH::CoinBagComponent::UpdatePos()
{
	if (m_PreviousPos == m_DesiredPos)
		return;

	m_LerpFactor += Time::GetDeltaTime() * m_LerpSpeed;

	if (m_LerpFactor <= 1.f)
	{
		m_CurrentPos = m_PreviousPos * (1 - m_LerpFactor) + m_DesiredPos * m_LerpFactor;
		m_IsMoving = true;
	}
	else
	{
		m_CurrentPos = m_DesiredPos;
		m_PreviousPos = m_DesiredPos;
		m_LerpFactor = 0.f;
		m_IsMoving = false;
	}

	glm::vec2 relPos{ m_CurrentPos.x - m_HitBox.m_Height / 2, m_CurrentPos.y - m_HitBox.m_Width / 2 };

	GetOwner()->SetLocalPosition({ relPos, 0 });

	m_HitBox.m_Left = relPos.x;
	m_HitBox.m_Bottom = relPos.y;
}

FH::Cell* FH::CoinBagComponent::GetCurrentCell()
{
	return m_pGridMap->GetCell(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol);
}

FH::Cell* FH::CoinBagComponent::GetNextCellDown()
{
	if (m_CurrentRow + 1 >= m_pGridMap->GetAmtRows())
		return nullptr;

	return m_pGridMap->GetCell((m_CurrentRow + 1) * m_pGridMap->GetAmtCols() + m_CurrentCol);
}

void FH::CoinBagComponent::SetNewCellTarget(int col, int row)
{
	GetCurrentCell()->m_HasBag = false;
	
	m_CurrentCol = col;
	m_CurrentRow = row;

	auto* pCurCell{ GetCurrentCell() };
	m_DesiredPos = pCurCell->m_Center;
	pCurCell->m_HasBag = true;
}