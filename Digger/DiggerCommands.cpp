#include "DiggerCommands.h"
#include "FHTime.h"
#include "PlayerComponent.h"
#include "SoundLocator.h"
#include "GridMapComponent.h"

FH::MoveCommand::MoveCommand(GameObject* pGameObject, const glm::vec2& direction,
	GridMapComponent* map)
	: Command(pGameObject)
	, m_Direction{ direction }
	, m_MaxCol{ map->GetAmtCols() - 1 }
	, m_MaxRow{ map->GetAmtRows() - 1 }
{
	m_pPlayer = pGameObject->GetComponentOfType<PlayerComponent>();
}

void FH::MoveCommand::Execute()
{
	if (m_pPlayer->IsMoving())
		return;

	int col{ m_pPlayer->GetCurrentCol() };
	int row{ m_pPlayer->GetCurrentRow() };

	if (m_Direction.x > 0)
		if(col != m_MaxCol)
			++col;
	if (m_Direction.x < 0)
		if(col != 0)
			--col;

	if (m_Direction.y > 0)
		if(row != m_MaxRow)
			++row;
	if (m_Direction.y < 0)
		if(row != 0)
			--row;

	m_pPlayer->SetNewCellTarget(col, row);
}

FH::AcceptCommand::AcceptCommand(GameObject* pGameObject)
	: Command(pGameObject)
{}

void FH::AcceptCommand::Execute()
{
	
}
