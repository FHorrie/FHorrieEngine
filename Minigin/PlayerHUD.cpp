#include "Subject.h"
#include "PlayerHUD.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "PlayerComponent.h"

FH::PlayerHUD::PlayerHUD(GameObject* pOwner)
	: Component(pOwner)
{
	int t1Idx = pOwner->AddComponent(std::make_unique<FH::TextComponent>(pOwner, "Lives: ", 0.f, 0.f, 20));
	int t2Idx = pOwner->AddComponent(std::make_unique<FH::TextComponent>(pOwner, "Score: ", 0.f, 20.f));

	m_pTextComponent[0] = dynamic_cast<TextComponent*>(pOwner->GetComponentWithIdx(t1Idx));
	m_pTextComponent[1] = dynamic_cast<TextComponent*>(pOwner->GetComponentWithIdx(t2Idx));
}

void FH::PlayerHUD::Update()
{
	if (m_NeedsUpdate)
	{
		m_pTextComponent[0]->SetText("Lives: " + std::to_string(m_Lives));
		m_pTextComponent[1]->SetText("Score: " + std::to_string(m_Score));
		m_NeedsUpdate = false;
	}
}

void FH::PlayerHUD::OnNotify(GameObject* go, GameEvent e)
{
	switch (e)
	{
	case FH::GameEvent::EVENT_INCREASE_SCORE:
		m_Score = go->GetComponentOfType<PlayerComponent>()->GetScore();
		m_NeedsUpdate = true;
		break;
	case FH::GameEvent::EVENT_ACTOR_HIT:
		m_Lives = go->GetComponentOfType<PlayerComponent>()->GetLives();
		m_NeedsUpdate = true;
		break;
	case FH::GameEvent::EVENT_ACTOR_KILLED:
		break;
	default:
		break;
	}
}