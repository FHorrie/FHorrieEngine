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

	const float x{ objectPos.x + m_Direction.x * float(Time::GetDeltaTime()) * m_MovementSpeed };
	const float y{ objectPos.y + m_Direction.y * float(Time::GetDeltaTime()) * m_MovementSpeed };
	const float z{ objectPos.z + m_Direction.z * float(Time::GetDeltaTime()) * m_MovementSpeed };

	const glm::vec3 pos{ x,y,z };

	GetGameObjectPtr()->SetLocalPosition(pos);
}

FH::AttackCommand::AttackCommand(GameObject* pGameObject)
	: Command(pGameObject)
{}

void FH::AttackCommand::Execute()
{
	AttackComponent* atkComp{ GetGameObjectPtr()->GetComponentOfType<AttackComponent*>()};

	if (atkComp == nullptr)
		throw std::runtime_error("No attack component was found!");

	atkComp->DefaultAttack();
}