#include <stdexcept>
#include <numeric>
#include <sstream>
#include "GameObject.h"
#include "FPSCounter.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "Time.h"

FH::FPSCounter::FPSCounter(GameObject* pOwner)
	: Component(pOwner)
{
	int idx = pOwner->AddComponent(std::make_unique<FH::TextComponent>(pOwner, "FPS:", 10.f, 10.f));

	//Keep raw ptr to instruct text, this is safe (for now)
	//We delete both this and the text comp when the object is destroyed
	m_pTextComponent = dynamic_cast<TextComponent*>(pOwner->GetComponentWithIdx(idx));
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
