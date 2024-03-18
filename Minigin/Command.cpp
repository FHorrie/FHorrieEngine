#include "Command.h"
#include "Time.h"

dae::MoveCommand::MoveCommand(GameObject* pGameObject, const glm::vec3& direction, float movementSpeed)
	: dae::Command(pGameObject)
	, m_Direction{ direction }
	, m_MovementSpeed{ movementSpeed }
{}

void dae::MoveCommand::Execute()
{
	auto objectPos{ GetGameObjectPtr()->GetTransform().GetPosition() };

	const float x{ objectPos.x + m_Direction.x * float(Time::GetDeltaTime()) * m_MovementSpeed };
	const float y{ objectPos.y + m_Direction.y * float(Time::GetDeltaTime()) * m_MovementSpeed };
	const float z{ objectPos.z + m_Direction.z * float(Time::GetDeltaTime()) * m_MovementSpeed };

	const glm::vec3 pos{ x,y,z };

	GetGameObjectPtr()->SetLocalPosition(pos);
}

//void MoveUp::Execute(dae::GameObject* gameObject)
//{
//	auto TransformComp = dynamic_cast<TransformComponent*>(gameObject->GetComponentWithIdx(0));
//	if (TransformComp)
//		TransformComp->SetPosValsToIncrease(glm::vec3(0.f, -1.f, 0.f));
//}
//
//void MoveDown::Execute(dae::GameObject* gameObject)
//{
//	auto TransformComp = dynamic_cast<TransformComponent*>(gameObject->GetComponentWithIdx(0));
//	if (TransformComp)
//		TransformComp->SetPosValsToIncrease(glm::vec3(0.f, 1.f, 0.f));
//}
//
//void MoveLeft::Execute(dae::GameObject* gameObject)
//{
//	auto TransformComp = dynamic_cast<TransformComponent*>(gameObject->GetComponentWithIdx(0));
//	if (TransformComp)
//		TransformComp->SetPosValsToIncrease(glm::vec3(-1.f, 0.f, 0.f));
//}
//
//void MoveRight::Execute(dae::GameObject* gameObject)
//{
//	auto TransformComp = dynamic_cast<TransformComponent*>(gameObject->GetComponentWithIdx(0));
//	if (TransformComp)
//		TransformComp->SetPosValsToIncrease(glm::vec3(1.f, 0.f, 0.f));
//}

//Make 1 move component with Direction
//Dont use the component, set position directly with "SetLocalPos"