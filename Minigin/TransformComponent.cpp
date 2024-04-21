#include "TransformComponent.h"
#include "GameObject.h"
#include "Time.h"

FH::TransformComponent::TransformComponent(GameObject* pOwner, float movementSpeed)
	: Component(pOwner)
	, m_PosValsToIncrease{}
	, m_MovementSpeed{ movementSpeed }
{
	m_OwnerPos = pOwner->GetTransform().GetPosition();
}

FH::TransformComponent::TransformComponent(GameObject* pOwner, glm::vec3 posToInc, float movementSpeed)
	: Component(pOwner)
	, m_PosValsToIncrease{ posToInc }
	, m_MovementSpeed{ movementSpeed }
{
	m_OwnerPos = pOwner->GetTransform().GetPosition();
}

void FH::TransformComponent::Update()
{
	const float x{ m_OwnerPos.x + m_PosValsToIncrease.x * float(Time::GetDeltaTime()) * m_MovementSpeed};
	const float y{ m_OwnerPos.y + m_PosValsToIncrease.y * float(Time::GetDeltaTime()) * m_MovementSpeed };
	const float z{ m_OwnerPos.z + m_PosValsToIncrease.z * float(Time::GetDeltaTime()) * m_MovementSpeed };

	const glm::vec3 pos{ x,y,z };

	m_OwnerPos = pos;
	m_PosValsToIncrease = glm::vec3{};

	GetOwner()->SetLocalPosition(pos);
}