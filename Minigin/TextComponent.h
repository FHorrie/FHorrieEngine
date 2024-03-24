#pragma once
#include <string>
#include <memory>
#include <SDL_ttf.h>
#include "Component.h"
#include "Transform.h"
#include "Texture2D.h"

namespace FH
{
	class Font;
	class TextComponent final : public Component
	{
	public:
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color) { m_Color = color; }
		void SetPosition(float x, float y) { m_Translate = glm::vec3(x, y, 0.f); }

		TextComponent(GameObject* pOwner, const std::string& text, float left = 0.f, float top = 0.f, int fontSize = 28.f);
		~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	protected:
		bool m_IsVisible{ true };
		bool m_NeedsUpdate{ true };
		std::string m_Text;
		SDL_Color m_Color;
		glm::vec3 m_Translate{};
		std::shared_ptr<Font> m_Font;
		std::unique_ptr<Texture2D> m_TextTexture;
	};
}

