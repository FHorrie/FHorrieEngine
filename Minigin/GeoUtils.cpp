#include "SDL_opengl.h"
#include "GeoUtils.h"

void utils::DrawRect(float left, float bottom, float width, float height, float lineWidth)
{
	if (width > 0 && height > 0 && lineWidth > 0)
	{

		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(left, bottom);
			glVertex2f(left + width, bottom);
			glVertex2f(left + width, bottom + height);
			glVertex2f(left, bottom + height);
		}
		glEnd();
	}
}

void utils::DrawRect(const Rect& rect, float lineWidth)
{
	utils::DrawRect(rect.m_Left, rect.m_Bottom, rect.m_Width, rect.m_Height, lineWidth);
}

bool utils::IsOverlapping(const Rect& r1, const Rect& r2)
{
	// If one rectangle is on left side of the other
	if ((r1.m_Left + r1.m_Width) < r2.m_Left || (r2.m_Left + r2.m_Width) < r1.m_Left)
		return false;

	// If one rectangle is under the other
	if (r1.m_Bottom > (r2.m_Bottom + r2.m_Height) || r2.m_Bottom > (r1.m_Bottom + r1.m_Height))
		return false;

	return true;
}