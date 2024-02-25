#pragma once
#include <string>
#include <memory>
#include <SDL_ttf.h>
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public Component
	{
	public:
		virtual void Update() override;
		void Render() const override;

		void SetText(const std::string& text) 
		{ 
			m_Text = text;
			m_NeedsUpdate = true;
		}
		void SetColor(const SDL_Color& color) { m_Color = color; }
		void SetPosition(float x, float y) { m_Transform.SetPosition(x, y, 0.f); }

		TextComponent(const std::string& text, std::shared_ptr<Font> font, float left = 0.f, float top = 0.f);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	protected:
		bool m_IsVisible{ true };
		bool m_NeedsUpdate{ true };
		std::string m_Text;
		SDL_Color m_Color;
		Transform m_Transform{};
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}
