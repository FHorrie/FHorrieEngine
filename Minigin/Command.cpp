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

FH::AttackCommand::AttackCommand(GameObject* pGameObject)
	: Command(pGameObject)
{}

void FH::AttackCommand::Execute()
{
	AttackComponent* atkComp{ GetGameObjectPtr()->GetComponentOfType<AttackComponent>()};

	if (atkComp == nullptr)
		throw std::runtime_error("No attack component was found!");

	atkComp->DefaultAttack(GetGameObjectPtr());
}

FH::GainScoreCommand::GainScoreCommand(GameObject* pGameObject, bool bigReward)
	: Command(pGameObject)
	, m_BigReward{ bigReward }
{}

void FH::GainScoreCommand::Execute()
{
	AttackComponent* atkComp{ GetGameObjectPtr()->GetComponentOfType<AttackComponent>() };

	if (atkComp == nullptr)
		throw std::runtime_error("No attack component was found!");

	atkComp->GainPoints(m_BigReward);
}