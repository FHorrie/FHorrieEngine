#include "DiggerCommands.h"
#include "FHTime.h"
#include "PlayerComponent.h"
#include "SoundLocator.h"

FH::MoveCommand::MoveCommand(GameObject* pGameObject, const glm::vec2& direction, float movementSpeed)
	: Command(pGameObject)
	, m_Direction{ direction }
	, m_MovementSpeed{ movementSpeed }
{
	m_pPlayer = pGameObject->GetComponentOfType<PlayerComponent>();
}

void FH::MoveCommand::Execute()
{
	if (m_pPlayer->IsMoving())
		return;

	constexpr int maxCol{ 15 - 1 };
	constexpr int maxRow{ 10 - 1 };

	int col{ m_pPlayer->GetCurrentCol() };
	int row{ m_pPlayer->GetCurrentRow() };

	if (m_Direction.x > 0)
		if(col != maxCol)
			++col;
	if (m_Direction.x < 0)
		if(col != 0)
			--col;

	if (m_Direction.y > 0)
		if(row != maxRow)
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
	auto& service{ SoundLocator::GetSoundService() };
	service.Play("Teleport", 0.3f);
}
