#pragma once
//#include "glm/glm.hpp"

struct Rect
{
	Rect() {}
	explicit Rect(float left, float bottom, float width, float height)
		: m_Left	{ left }
		, m_Bottom	{ bottom }
		, m_Width	{ width }
		, m_Height	{ height }
	{}

	float m_Left{};
	float m_Bottom{};
	float m_Width{};
	float m_Height{};
};