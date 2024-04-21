#include "Command.h"
#include "Time.h"
#include "AttackComponent.h"

FH::MoveCommand::MoveCommand(GameObject* pGameObject, const glm::vec3& direction, float movementSpeed)
	: Command(pGameObject)
	, m_Direction{ direction }
	, m_MovementSpeed{ movementSpeed }
{}

void FH::MoveCommand::Execute()
{
	auto objectPos{ GetGameObjectPtr()->GetTransform().GetPosition() };
	const glm::vec3 pos{ objectPos + m_Direction * float(Time::GetDeltaTime()) * m_MovementSpeed };
	GetGameObjectPtr()->SetLocalPosition(pos);
}

FH::AcceptCommand::AcceptCommand(GameObject* pGameObject)
	: Command(pGameObject)
{}

void FH::AcceptCommand::Execute()
{
	
}
