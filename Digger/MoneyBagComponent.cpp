#include "MoneyBagComponent.h"
#include "GeoUtils.h"
#include "FHTime.h"
#include "GameObject.h"
#include "Subject.h"
#include "Renderer.h"
#include "PlayerComponent.h"

FH::MoneyBagComponent::MoneyBagComponent(GameObject* pOwner, int col, int row,
	GridMapComponent* pGridMap, PlayerComponent* pPlayer)
	: Component{ pOwner }
	, m_CurrentCol{ col }
	, m_CurrentRow{ row }
	, m_pGridMap{ pGridMap }
	, m_pPlayer{ pPlayer }
{
	m_pRenderer = Renderer::GetInstance().GetSDLRenderer();

	if (col < 0 || col > m_pGridMap->GetAmtCols() - 1)
		throw std::exception("col out of range");
	if (row < 0 || row > m_pGridMap->GetAmtRows() - 1)
		throw std::exception("row out of range");

	m_pGridMap->SetCellContainsBag(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol, true);

	const auto cellPos{ m_pGridMap->GetCell(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol).m_Center };

	m_PreviousPos = cellPos;
	m_CurrentPos = cellPos;
	m_DesiredPos = cellPos;


	const glm::vec2 playerPos{ cellPos.x - m_HitBox.m_Width / 2,  cellPos.y - m_HitBox.m_Height / 2 };

	m_HitBox.m_Left = playerPos.x;
	m_HitBox.m_Bottom = playerPos.y;

	GetOwner()->SetLocalPosition({ playerPos, 0 });
}

void FH::MoneyBagComponent::Update()
{
	UpdatePos();
	m_State->Update(this);
}

void FH::MoneyBagComponent::Render() const
{
	utils::RectFunctions::DrawRect(m_pRenderer, m_HitBox);
}

void FH::MoneyBagComponent::UpdatePos()
{
	if (m_PreviousPos == m_DesiredPos)
		return;

	m_LerpFactor += (float)Time::GetDeltaTime() * m_LerpSpeed;

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

FH::Cell FH::MoneyBagComponent::GetNextCellDown()
{
	if (m_CurrentRow + 1 >= m_pGridMap->GetAmtRows())
		return Cell();

	return m_pGridMap->GetCell((m_CurrentRow + 1) * m_pGridMap->GetAmtCols() + m_CurrentCol);
}

void FH::MoneyBagComponent::SetNewCellTarget(int col, int row)
{
	m_pGridMap->SetCellContainsBag(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol, false);
	m_CurrentCol = col;
	m_CurrentRow = row;
	m_DesiredPos = m_pGridMap->GetCell(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol).m_Center;
	m_pGridMap->SetCellContainsBag(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol, true);
}

FH::PlayerComponent* FH::MoneyBagComponent::GetPlayer() const
{
	return m_pPlayer;
}