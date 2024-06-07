#pragma once
#include <SDL.h>
#include <array>
#include "Singleton.h"

namespace FH
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_renderer; };

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

		static constexpr int GetLogicalWidth() { return LOGICALWIDTH; }
		static constexpr int GetLogicalHeight() { return LOGICALHEIGHT; }

	private:
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};

		static constexpr int LOGICALWIDTH{ 320 };
		static constexpr int LOGICALHEIGHT{ 200 };

	};
}

