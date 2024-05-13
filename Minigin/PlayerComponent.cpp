#include "PlayerComponent.h"
#include "GeoUtils.h"
#include "GameObject.h"
#include "Subject.h"
#include "Renderer.h"
#include "../Digger/GridMapComponent.h"
#include "FHTime.h"

FH::PlayerComponent::PlayerComponent(GameObject* pOwner, int col, int row, 
	GridMapComponent* pGridMap)
	: Component{ pOwner }
	, m_CurrentCol{ col }
	, m_CurrentRow{ row }
	, m_pGridMap{ pGridMap }
{
	m_pRenderer = Renderer::GetInstance().GetSDLRenderer();

	if (col < 0 || col > m_pGridMap->GetAmtCols() - 1)
		throw std::exception("col out of range");
	if (row < 0 || row > m_pGridMap->GetAmtRows() - 1)
		throw std::exception("row out of range");

	m_pGridMap->SetCellVisited(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol);

	const auto cellPos{ m_pGridMap->GetCell(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol).m_Center };

	m_PreviousPos = cellPos;
	m_CurrentPos = cellPos;
	m_DesiredPos = cellPos;

	const glm::vec2 playerPos{ cellPos.x - m_HitBox.m_Width / 2,  cellPos.y - m_HitBox.m_Height / 2 };

	m_HitBox.m_Left = playerPos.x;
	m_HitBox.m_Bottom = playerPos.y;

	GetOwner()->SetLocalPosition({ playerPos, 0 });
}

FH::PlayerComponent::PlayerComponent(GameObject* pOwner, int col, int row, int lives,
	GridMapComponent* pGridMap)
	: PlayerComponent{ pOwner, col, row, pGridMap }
{
	m_Lives = lives;
}

void FH::PlayerComponent::Update()
{
	UpdatePos();
}

void FH::PlayerComponent::Render() const
{
	utils::RectFunctions::DrawRect(m_pRenderer, m_HitBox);
}

void FH::PlayerComponent::UpdatePos()
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

void FH::PlayerComponent::SetNewCellTarget(int col, int row)
{
	m_PreviousCol = m_CurrentCol;
	m_PreviousRow = m_CurrentRow;

	m_CurrentCol = col;
	m_CurrentRow = row;

	auto newCell{ m_pGridMap->GetCell(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol) };

	m_DesiredPos = newCell.m_Center;
	if (newCell.m_IsVisited)
		m_LerpSpeed = 3.f;
	else
		m_LerpSpeed = 2.f;

	m_pGridMap->SetCellVisited(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol);
}

void FH::PlayerComponent::GainPoints(bool bigReward)
{
	if (bigReward)
		m_Score += 100;
	else
		m_Score += 10;
	Notify(GetOwner(), GameEvent::EVENT_INCREASE_SCORE);

	if (m_Score >= 500)
		Notify(GetOwner(), GameEvent::EVENT_SCORE_500);
}

void FH::PlayerComponent::DefaultAttack(GameObject* Target)
{
	if (!m_IsDead)
	{
		auto targetAttackComp = Target->GetComponentOfType<PlayerComponent>();

		if (utils::RectFunctions::IsOverlapping(m_HitBox, targetAttackComp->GetHitBox()))
		{
			targetAttackComp->TakeDamage(1);
		}
	}
}

void FH::PlayerComponent::TakeDamage(int damage)
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

