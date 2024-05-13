#pragma once
#include "GeoStructs.h"

struct SDL_Renderer;
namespace utils
{
	struct RectFunctions
	{
		static void DrawRect(SDL_Renderer* renderer, 
			float left, float bottom, float width, float height, Color4f color = {});
		static void DrawRect(SDL_Renderer* renderer, const Rect& rect, Color4f color = {});

		static void DrawFillRect(SDL_Renderer* renderer,
			float left, float bottom, float width, float height, Color4f color = {});
		static void DrawFillRect(SDL_Renderer* renderer, const Rect& rect, Color4f color = {});

		static bool IsOverlapping(const Rect& r1, const Rect& r2);
	};

}