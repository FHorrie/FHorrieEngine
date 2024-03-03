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

		TransformComponent(std::shared_ptr<GameObject> pOwner);
		TransformComponent(std::shared_ptr<GameObject> pOwner, glm::vec3 posToInc);
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

