#pragma once
#include "TransformComponent.h"

namespace dae
{
	class RotationComponent final : public TransformComponent
	{
	public:
		void Update() override;

		RotationComponent(std::shared_ptr<GameObject> pOwner, float rotSpeed = 1.f)
			: TransformComponent(pOwner)
			, m_Speed{ rotSpeed }
		{}
		RotationComponent(std::shared_ptr<GameObject> pOwner, glm::vec3 posToInc, float rotSpeed = 1.f)
			: TransformComponent(pOwner, posToInc)
			, m_Speed{ rotSpeed }
		{}
		virtual ~RotationComponent() = default;
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = default;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = default;
		
	private:
		float m_Speed;
		float m_Angle{};
	};
}