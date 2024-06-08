#include <iostream>

#include "PlayerComponent.h"
#include "GeoUtils.h"
#include "GameObject.h"
#include "Subject.h"
#include "Renderer.h"
#include "../Digger/GridMapComponent.h"
#include "FHTime.h"
#include "SoundLocator.h"

FH::PlayerComponent::PlayerComponent(GameObject* pOwner, GridMapComponent* pGridMap)
	: Component{ pOwner }
	, m_pGridMap{ pGridMap }
	, m_pRenderer{ Renderer::GetInstance().GetSDLRenderer() }
{}

FH::PlayerComponent::PlayerComponent(GameObject* pOwner, int col, int row, 
	GridMapComponent* pGridMap)
	: PlayerComponent(pOwner, pGridMap)
{
	SetCellPos(col, row);
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
	UpdateGemReward();
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

FH::Cell* FH::PlayerComponent::GetCurrentCell()
{
	return m_pGridMap->GetCell(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol);
}

void FH::PlayerComponent::SetNewCellTarget(int col, int row)
{
	auto* newCell{ m_pGridMap->GetCell(row * m_pGridMap->GetAmtCols() + col) };

	const int colDiff{ col - m_CurrentCol };
	const int rowDiff{ row - m_CurrentRow };

	if (colDiff > 0)
		Notify(GetOwner(), GameEvent::EVENT_PLAYER_MOVED_RIGHT);
	else if(colDiff < 0)
		Notify(GetOwner(), GameEvent::EVENT_PLAYER_MOVED_LEFT);
	else if (rowDiff > 0)
		Notify(GetOwner(), GameEvent::EVENT_PLAYER_MOVED_DOWN);
	else if (rowDiff < 0)
		Notify(GetOwner(), GameEvent::EVENT_PLAYER_MOVED_UP);

	if (newCell->m_HasBag && rowDiff != 0)
		return;

	GetCurrentCell()->m_HasPlayer = false;

	m_PreviousCol = m_CurrentCol;
	m_PreviousRow = m_CurrentRow;

	m_CurrentCol = col;
	m_CurrentRow = row;


	m_DesiredPos = newCell->m_Center;
	if (newCell->m_IsVisited)
		m_LerpSpeed = 2.4f;
	else
		m_LerpSpeed = 1.8f;

	newCell->m_HasPlayer = true;
	newCell->m_IsVisited = true;
}

void FH::PlayerComponent::GainPoints(PointType type)
{
	auto& service{ SoundLocator::GetSoundService() };
	
	switch (type)
	{
	case FH::PointType::GemType:
		service.Play("GemGrabBase", 0.4f);
		GainGemReward();
		service.Play("GemGrab" + std::to_string(m_GemStreak), 0.45f);
		break;
	case FH::PointType::CoinType:
		m_Score += 500;
		service.Play("CoinGrab", 0.3f);
		break;
	case FH::PointType::EnemyKillType:
		m_Score += 250;
		break;
	default:
		break;
	}


	std::cout << "NEW PLAYER SCORE: " + std::to_string(m_Score) << std::endl;
}

void FH::PlayerComponent::GainGemReward()
{
	m_AccuGemTime = 0;
	++m_GemStreak;
	if (m_GemStreak == 8)
		m_Score += 250;
	else
		m_Score += 25;
}

void FH::PlayerComponent::UpdateGemReward()
{
	if (m_GemStreak == 8)
		m_GemStreak = 0;

	if (m_GemStreak == 0)
		return;

	m_AccuGemTime += Time::GetDeltaTime();

	if (m_AccuGemTime >= m_GemTime)
		m_GemStreak = 0;
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

void FH::PlayerComponent::SetCellPos(int col, int row)
{
	if (col < 0 || col > m_pGridMap->GetAmtCols() - 1)
		throw std::exception("col out of range");
	if (row < 0 || row > m_pGridMap->GetAmtRows() - 1)
		throw std::exception("row out of range");

	m_CurrentCol = col;
	m_CurrentRow = row;

	const auto cellPos{ m_pGridMap->GetCell(row * m_pGridMap->GetAmtCols() + col)->m_Center };

	m_PreviousPos = cellPos;
	m_CurrentPos = cellPos;
	m_DesiredPos = cellPos;

	const glm::vec2 playerPos{ cellPos.x - m_HitBox.m_Width / 2,  cellPos.y - m_HitBox.m_Height / 2 };

	m_HitBox.m_Left = playerPos.x;
	m_HitBox.m_Bottom = playerPos.y;

	GetOwner()->SetLocalPosition({ playerPos, 0 });

	m_pGridMap->SetCellVisited(m_CurrentRow * m_pGridMap->GetAmtCols() + m_CurrentCol);
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
		}
	}
}

