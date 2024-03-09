#include "TransformComponent.h"
#include "Time.h"

using namespace dae;

TransformComponent::TransformComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_PosValsToIncrease{}
{
	m_OwnerPos = pOwner->GetTransform().GetPosition();
}

TransformComponent::TransformComponent(GameObject* pOwner, glm::vec3 posToInc)
	: Component(pOwner)
	, m_PosValsToIncrease{ posToInc }
{
	m_OwnerPos = pOwner->GetTransform().GetPosition();
}

void TransformComponent::Update()
{
	const float x{ m_OwnerPos.x + m_PosValsToIncrease.x * float(Time::GetDeltaTime()) };
	const float y{ m_OwnerPos.y + m_PosValsToIncrease.y * float(Time::GetDeltaTime()) };
	const float z{ m_OwnerPos.z + m_PosValsToIncrease.z * float(Time::GetDeltaTime()) };

	const glm::vec3 pos{ x,y,z };

	m_OwnerPos = pos;

	GetOwner()->SetLocalPosition(pos);
}