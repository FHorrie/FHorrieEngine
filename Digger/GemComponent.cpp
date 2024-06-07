#include <glm/vec2.hpp>

#include "GemComponent.h"
#include "GameObject.h"
#include "GridMapComponent.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"

FH::GemComponent::GemComponent(GameObject* pOwner, int col, int row, 
	GridMapComponent* pGridMap, PlayerComponent* pPlayer)
	: Component(pOwner)
	, m_Cell{ pGridMap->GetCell(row * pGridMap->GetAmtCols() + col) }
	, m_pPlayer{ pPlayer }
{
	if (col < 0 || col > pGridMap->GetAmtCols() - 1)
		throw std::exception("col out of range");
	if (row < 0 || row > pGridMap->GetAmtRows() - 1)
		throw std::exception("row out of range");

	m_Cell->m_HasGem = true;

	const auto cellPos{ m_Cell->m_Center };
	const glm::vec2 playerPos{ cellPos.x - m_HitBox.m_Width / 2,  cellPos.y - m_HitBox.m_Height / 2 };

	m_HitBox.m_Left = playerPos.x;
	m_HitBox.m_Bottom = playerPos.y;

	m_GemTex = static_cast<TextureComponent*>
		(pOwner->AddComponent(std::make_unique<TextureComponent>(pOwner)).pComponent);

	m_GemTex->SetTexture("Gem");

	m_GemTex->SetPosition(playerPos.x, playerPos.y);
}

void FH::GemComponent::Update()
{
	if (m_Cell->m_HasPlayer && !m_PickedUp)
	{
		m_pPlayer->GainPoints(PointType::GemType);
		m_GemTex->SetHidden(true);
		m_PickedUp = true;
	}
}