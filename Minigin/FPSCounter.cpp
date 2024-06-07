#include <stdexcept>
#include <numeric>
#include <sstream>
#include "GameObject.h"
#include "FPSCounter.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "FHTime.h"

FH::FPSCounter::FPSCounter(GameObject* pOwner)
	: Component(pOwner)
{
	ComponentData textComponentData{ pOwner->AddComponent(std::make_unique<FH::TextComponent>(pOwner, "FPS:", 10.f, 10.f)) };

	m_pTextComponent = dynamic_cast<TextComponent*>(textComponentData.pComponent);
}

FH::FPSCounter::FPSCounter(GameObject* pOwner, int fontSize)
	: Component(pOwner)
{
	ComponentData textComponentData{ pOwner->AddComponent(std::make_unique<FH::TextComponent>(pOwner, "FPS:", 10.f, 10.f, fontSize)) };

	//Keep raw ptr to instruct text, this is safe since both exist while the scene exists
	m_pTextComponent = dynamic_cast<TextComponent*>(textComponentData.pComponent);
}

void FH::FPSCounter::Update()
{
	if (m_pTextComponent == nullptr)
		return;

	++m_FrameCalls;
	m_AccuTime += Time::GetDeltaTime();

	if (m_AccuTime >= MAXTIME)
	{
		//TODO: change to std::format
		std::stringstream stream;

		stream << std::fixed << std::setprecision(FLOATINGPOINTACURRACY) << float(m_FrameCalls / m_AccuTime);

		const std::string finalText = "FPS: " + stream.str();
		m_AccuTime = 0;
		m_FrameCalls = 0;

		m_pTextComponent->SetText(finalText);
	}
}
