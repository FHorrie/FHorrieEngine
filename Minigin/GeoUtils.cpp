#include <SDL.h>
#include "GeoUtils.h"

void utils::RectFunctions::DrawRect(SDL_Renderer* renderer, 
	float left, float bottom, float width, float height, Color4f color)
{
	SDL_FRect rect{ left, bottom, width, height };
	SDL_SetRenderDrawColor(renderer, color.m_Red, color.m_Green, color.m_Blue, color.m_Alpha);
	SDL_RenderDrawRectF(renderer, &rect);
}

void utils::RectFunctions::DrawRect(SDL_Renderer* renderer, const Rect& rect, Color4f color)
{
	DrawRect(renderer, rect.m_Left, rect.m_Bottom, rect.m_Width, rect.m_Height, color);
}

void utils::RectFunctions::DrawFillRect(SDL_Renderer* renderer, 
	float left, float bottom, float width, float height, Color4f color)
{
	SDL_FRect rect{ left, bottom, width, height };
	SDL_SetRenderDrawColor(renderer, color.m_Red, color.m_Green, color.m_Blue, color.m_Alpha);
	SDL_RenderFillRectF(renderer, &rect);
}

void utils::RectFunctions::DrawFillRect(SDL_Renderer* renderer, const Rect& rect, Color4f color)
{
	DrawFillRect(renderer, rect.m_Left, rect.m_Bottom, rect.m_Width, rect.m_Height, color);
}

bool utils::RectFunctions::IsOverlapping(const Rect& r1, const Rect& r2)
{
	// If one rectangle is on left side of the other
	if ((r1.m_Left + r1.m_Width) < r2.m_Left || (r2.m_Left + r2.m_Width) < r1.m_Left)
		return false;

	// If one rectangle is under the other
	if (r1.m_Bottom > (r2.m_Bottom + r2.m_Height) || r2.m_Bottom > (r1.m_Bottom + r1.m_Height))
		return false;

	return true;
}