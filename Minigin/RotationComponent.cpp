#include "RotationComponent.h"
#include "GameObject.h"
#include "Time.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace FH;

void RotationComponent::Update()
{
	m_Angle += m_Speed * float(Time::GetDeltaTime());

	if (m_Angle >= float(2 * M_PI) || m_Angle <= -float(2 * M_PI))
		m_Angle = 0;

	const float x{m_PosValsToIncrease.x * float(glm::cos(m_Angle)) };
	const float y{m_PosValsToIncrease.y * float(glm::sin(m_Angle)) };

	GetOwner()->SetLocalPosition(glm::vec3(x, y, 0.f));
}