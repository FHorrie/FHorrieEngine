#include "Transform.h"

using namespace dae;

void Transform::SetPosition(float x, float y, float z)
{
	SetPosition(glm::vec3(x, y, z));
}

void Transform::SetPosition(glm::vec3 pos)
{
	m_position = pos;
}

Transform dae::Transform::operator+(const Transform& lhs)
{
	Transform transform{};
	transform.m_position = m_position + lhs.m_position;
	return transform;
}