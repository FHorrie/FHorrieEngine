#include "RotationComponent.h"
#include "Time.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace dae;

void RotationComponent::Update()
{
	m_Angle += m_Speed * float(Time::GetDeltaTime());

	const float x{m_PosValsToIncrease.x * float(glm::cos(m_Angle)) };

	const float y{m_PosValsToIncrease.y * float(glm::sin(m_Angle)) };

	const glm::vec3 pos{ x,y,0.f };

	GetOwner().lock()->SetLocalPosition(pos);
}