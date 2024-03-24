#pragma once
#include "GeoStructs.h"

namespace utils
{
	void DrawRect(float left, float bottom, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Rect& rect, float lineWidth = 1.0f);
	
	bool IsOverlapping(const Rect& r1, const Rect& r2);
}