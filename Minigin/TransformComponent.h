#pragma once
#include "Component.h"

namespace FH
{
	class TransformComponent : public Component
	{
	public:
		void Update() override;
		void Render() const override {};

		void SetPosValsToIncrease(glm::vec3 posToInc) { m_PosValsToIncrease = posToInc; }

		TransformComponent(GameObject* pOwner, float movementSpeed = 1.f);
		TransformComponent(GameObject* pOwner, glm::vec3 posToInc, float movementSpeed = 1.f);
		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = default;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = default;

	protected:
		glm::vec3 m_OwnerPos{};
		glm::vec3 m_PosValsToIncrease;
		float m_MovementSpeed;
	};
}

