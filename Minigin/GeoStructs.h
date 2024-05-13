#pragma once
#include <cstdint>
//#include "glm/glm.hpp"

namespace utils
{
	struct Rect
	{
		Rect() = default;
		Rect(float left, float bottom, float width, float height)
			: m_Left{ left }
			, m_Bottom{ bottom }
			, m_Width{ width }
			, m_Height{ height }
		{}

		float m_Left{};
		float m_Bottom{};
		float m_Width{};
		float m_Height{};
	};

	struct Color4f
	{
		Color4f() = default;
		Color4f(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
			: m_Red{ r }
			, m_Green{ g }
			, m_Blue{ b }
			, m_Alpha{ a }
		{}

		uint8_t m_Red{ 255 };
		uint8_t m_Green{ 255 };
		uint8_t m_Blue{ 255 };
		uint8_t m_Alpha{ 255 };
	};
}