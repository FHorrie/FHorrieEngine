#include "ProjectileComponent.h"
#include "GridMapComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "LiveTextureComponent.h"
#include "SoundLocator.h"
#include "FHTime.h"

FH::ProjectileComponent::ProjectileComponent(GameObject* pOwner, int col, int row, glm::vec2 dir,
	GridMapComponent* pGridMap, PlayerComponent* pPlayer)
	: Component(pOwner)
	, m_CurrentCol{ col }
	, m_CurrentRow{ row }
	, m_ColDir{ static_cast<int>(dir.x) }
	, m_RowDir{ static_cast<int>(dir.y) }
	, m_pGridMap{ pGridMap }
	, m_pPlayer{ pPlayer }
{
	if (col < 0 || col > m_pGridMap->GetAmtCols() - 1)
		throw std::exception("col out of range");
	if (row < 0 || row > m_pGridMap->GetAmtRows() - 1)
		throw std::exception("row out of range");

	const auto cellPos{ GetCell()->m_Center };

	m_PreviousPos = cellPos;
	m_CurrentPos = cellPos;
	m_DesiredPos = cellPos;

	const glm::vec2 bagPos{ cellPos.x - m_HitBox.m_Width / 2,  cellPos.y - m_HitBox.m_Height / 2 };

	m_HitBox.m_Left = bagPos.x;
	m_HitBox.m_Bottom = bagPos.y;

	pOwner->SetLocalPosition({ bagPos, 0 });

	m_ProjectileTex = static_cast<LiveTextureComponent*>
		(pOwner->AddComponent(std::make_unique<LiveTextureComponent>(pOwner, 0.1f, false)).pComponent);

	m_ProjectileTex->AddSprites({ "Fire1", "Fire2", "Fire3", "Fire2" });
}

void FH::ProjectileComponent::Update()
{
	CheckPath();
	UpdatePos();
}

void FH::ProjectileComponent::UpdatePos()
{
	if (m_PreviousPos == m_DesiredPos || m_Broken)
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

	if (m_WillBreak && m_LerpFactor >= 0.3f)
	{
		DestroyBall();
	}

	glm::vec2 relPos{ m_CurrentPos.x - m_HitBox.m_Height / 2, m_CurrentPos.y - m_HitBox.m_Width / 2 };

	GetOwner()->SetLocalPosition({ relPos, 0 });

	m_HitBox.m_Left = relPos.x;
	m_HitBox.m_Bottom = relPos.y;
}

void FH::ProjectileComponent::CheckPath()
{
	if (!m_IsMoving && !m_WillBreak)
	{
		auto* nextCell{ GetCell(m_ColDir, m_RowDir) };
		if (nextCell == nullptr)
		{
			DestroyBall();
			return;
		}

		if (nextCell->m_IsVisited)
			SetNewCellTarget(nextCell->m_Col, nextCell->m_Row);
		else
			SetNewCellTarget(nextCell->m_Col, nextCell->m_Row, true);
	}
}
void FH::ProjectileComponent::DestroyBall()
{
	m_ProjectileTex->SetHidden(true);
	m_WillBreak = true;
	m_Broken = true;
	SoundLocator::GetSoundService().Play("BallBreak", 0.3f);
}

void FH::ProjectileComponent::SetNewCellTarget(int col, int row, bool willBreak)
{
	m_CurrentCol = col;
	m_CurrentRow = row;

	auto* pCurCell{ GetCell() };
	m_DesiredPos = pCurCell->m_Center;
	m_WillBreak = willBreak;
}

FH::Cell* FH::ProjectileComponent::GetCell(int colDir, int rowDir)
{
	if (m_pGridMap->GetAmtCols() == (m_CurrentCol + colDir) || 0 == (m_CurrentCol + colDir))
		return nullptr;

	return m_pGridMap->GetCell((m_CurrentRow + rowDir) * m_pGridMap->GetAmtCols() + (m_CurrentCol + colDir));
}