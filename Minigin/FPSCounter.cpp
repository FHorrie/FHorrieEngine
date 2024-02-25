#include <stdexcept>
#include <numeric>
#include <sstream>
#include "FPSCounter.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "Time.h"

using namespace dae;

FPSCounter::FPSCounter(std::shared_ptr<Font> font, float left, float top)
	: TextComponent("FPS: 0", font, left, top)
{}

void FPSCounter::Update()
{
	m_FPSStored[m_FPSCount] = (1.f / (float)Time::GetDeltaTime());
	++m_FPSCount;

	if (m_FPSCount == FPSBUFFER)
	{
		float average{ std::reduce(m_FPSStored.cbegin(), m_FPSStored.cend()) / FPSBUFFER };

		std::stringstream stream;

		stream << std::fixed << std::setprecision(FLOATINGPOINTACURRACY) << average;

		m_Text = "FPS: " + stream.str();
		m_FPSCount = 0;
		m_NeedsUpdate = true;
	}

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
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}
