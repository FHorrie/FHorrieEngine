#include <stdexcept>
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Font.h"

FH::TextComponent::TextComponent(GameObject* pOwner, const std::string& text, float left, float top, int fontSize)
	: Component(pOwner)
	, m_Text{ text }
	, m_Color{ 255,255,255,255 }
	, m_Font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize) }
	, m_TextTexture{ nullptr }
{
	m_Translate = glm::vec3(left, top, 0.f); //z = 0 for now, 2D view 
}

void FH::TextComponent::SetText(const std::string& text)
{
	if (m_Text != text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}
}

void FH::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_unique<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void FH::TextComponent::Render() const
{
	if (m_TextTexture != nullptr && m_IsVisible == true)
	{
		const auto& pos = m_Translate + GetParentTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}