#include <iostream>

#include "PlayerComponent.h"
#include "GeoUtils.h"
#include "GameObject.h"
#include "Subject.h"
#include "Renderer.h"
#include "FHTime.h"
#include "SoundLocator.h"
#include "GridMapComponent.h"
#include "ProjectileComponent.h"
#include "SceneManager.h"

FH::PlayerComponent::PlayerComponent(GameObject* pOwner, GridMapComponent* pGridMap)
	: Component{ pOwner }
	, m_pGridMap{ pGridMap }
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
	UpdateAttackTime();
	Respawn();
}

void FH::PlayerComponent::UpdatePos()
{
	if (m_PreviousPos == m_DesiredPos || m_IsDead)
		return;

	m_LerpFactor += (float)Time::GetDeltaTime() * m_LerpSpeed;

	if (m_LerpFactor < 1.f)
	{
		m_CurrentPos = m_PreviousPos * (1 - m_LerpFactor) + m_DesiredPos * m_LerpFactor;
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
	if (m_IsDead)
		return;

	m_ColDir = col - m_CurrentCol;
	m_RowDir = row - m_CurrentRow;

	if (!m_ColDir && !m_RowDir)
		return;

	auto* newCell{ m_pGridMap->GetCell(row * m_pGridMap->GetAmtCols() + col) };

	if (newCell == nullptr)
		return;

	if (m_ColDir > 0)
		Notify(GetOwner(), GameEvent::EVENT_PLAYER_MOVED_RIGHT);
	else if(m_ColDir < 0)
		Notify(GetOwner(), GameEvent::EVENT_PLAYER_MOVED_LEFT);
	else if (m_RowDir > 0)
		Notify(GetOwner(), GameEvent::EVENT_PLAYER_MOVED_DOWN);
	else if (m_RowDir < 0)
		Notify(GetOwner(), GameEvent::EVENT_PLAYER_MOVED_UP);

	if (newCell->m_HasBag && m_RowDir != 0)
		return;

	GetCurrentCell()->m_HasPlayer = false;

	m_CurrentCol = col;
	m_CurrentRow = row;


	m_DesiredPos = newCell->m_Center;
	if (newCell->m_IsVisited)
		m_LerpSpeed = 2.4f;
	else
		m_LerpSpeed = 1.8f;

	newCell->m_HasPlayer = true;
	newCell->m_IsVisited = true;

	m_IsMoving = true;
}

void FH::PlayerComponent::SetCellPos(int col, int row)
{
	if (col < 0 || col > m_pGridMap->GetAmtCols() - 1)
		throw std::exception("col out of range");
	if (row < 0 || row > m_pGridMap->GetAmtRows() - 1)
		throw std::exception("row out of range");

	m_RespawnCol = col;
	m_RespawnRow = row;

	m_CurrentCol = col;
	m_CurrentRow = row;

	auto* cell{ m_pGridMap->GetCell(row * m_pGridMap->GetAmtCols() + col) };

	const auto cellPos{ cell->m_Center };

	m_PreviousPos = cellPos;
	m_CurrentPos = cellPos;
	m_DesiredPos = cellPos;

	const glm::vec2 playerPos{ cellPos.x - m_HitBox.m_Width / 2,  cellPos.y - m_HitBox.m_Height / 2 };

	m_HitBox.m_Left = playerPos.x;
	m_HitBox.m_Bottom = playerPos.y;

	GetOwner()->SetLocalPosition({ playerPos, 0 });

	cell->m_IsVisited = true;
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
		service.Play("CoinGrab", 0.2f);
		break;
	case FH::PointType::EnemyKillType:
		m_Score += 250;
		break;
	default:
		break;
	}

	Notify(GetOwner(), GameEvent::EVENT_PLAYER_GAINED_POINTS);

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

void FH::PlayerComponent::UpdateAttackTime()
{
	if(m_AccuAttackTime < m_AttackTime)
		m_AccuAttackTime += Time::GetDeltaTime();
}

void FH::PlayerComponent::DefaultAttack()
{
	if (m_AccuAttackTime < m_AttackTime || m_IsDead)
		return;

	auto fireObj = std::make_unique<FH::GameObject>();
	fireObj->AddComponent(
		std::make_unique<ProjectileComponent>(
			fireObj.get(), m_CurrentCol, m_CurrentRow, glm::vec2(m_ColDir, m_RowDir), m_pGridMap, this));

	SceneManager::GetInstance().GetCurrentScene()->Add(std::move(fireObj));

	SoundLocator::GetSoundService().Play("BallShot", 0.3f);

	m_AccuAttackTime = 0;
}

void FH::PlayerComponent::Die()
{
	m_IsDead = true;
	--m_Lives;

	Notify(GetOwner(), GameEvent::EVENT_PLAYER_DIED);
	SoundLocator::GetSoundService().Play("PlayerDied", 0.3f);
	SoundLocator::GetSoundService().PlaySong("DeathBGM", 0.3f, false);
}

void FH::PlayerComponent::Respawn()
{
	if (!m_IsDead || m_Lives <= 0)
		return;

	if (m_AccuRespawnTime < m_RespawnTime)
	{
		m_AccuRespawnTime += Time::GetDeltaTime();
		return;
	}

	SetCellPos(m_RespawnCol, m_RespawnRow);
	Notify(GetOwner(), GameEvent::EVENT_PLAYER_MOVED_LEFT);
	m_IsDead = false;
	m_IsMoving = false;
	m_LerpFactor = 0;
	m_ColDir = -1;
	m_RowDir = 0;
	m_AccuRespawnTime = 0;

	SoundLocator::GetSoundService().PlaySong("MainBGM", 0.4f, true);
}

