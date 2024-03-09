#pragma once
#include "Component.h"

namespace dae
{
	class TransformComponent : public Component
	{
	public:
		virtual void Update() override;
		void Render() const override {};

		void SetPosValsToIncrease(glm::vec3 posToInc) { m_PosValsToIncrease = posToInc; }

		TransformComponent(GameObject* pOwner);
		TransformComponent(GameObject* pOwner, glm::vec3 posToInc);
		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = default;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = default;
	protected:
		glm::vec3 m_OwnerPos{};
		glm::vec3 m_PosValsToIncrease;
	};
}

