#include "ScoreComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"
#include "ResourceManager.h"

FH::ScoreComponent::ScoreComponent(GameObject* pOwner, PlayerComponent* pPlayer)
	: Component(pOwner)
	, m_pPlayer{ pPlayer }
{
	for (int i{}; i < LETTERAMT; ++i)
	{
		m_NumberTexArr[i] = static_cast<TextureComponent*>
			(pOwner->AddComponent(std::make_unique<TextureComponent>(pOwner)).pComponent);

		m_NumberTexArr[i]->SetTexture("0");

		m_NumberTexArr[i]->SetPosition(float(MARGIN + LETTERSIZE * i), float(MARGIN));
	}

	pPlayer->AddObserver(this);
}

void FH::ScoreComponent::OnNotify(GameObject* go, GameEvent e)
{
	go;

	if (e == GameEvent::EVENT_PLAYER_GAINED_POINTS)
	{
		const int score = m_pPlayer->GetScore();

		m_NumberTexArr[4]->SetTexture(std::to_string(score % 10));
		m_NumberTexArr[3]->SetTexture(std::to_string((score / 10) % 10));
		m_NumberTexArr[2]->SetTexture(std::to_string((score / 100) % 10));
		m_NumberTexArr[1]->SetTexture(std::to_string((score / 1000) % 10));
		m_NumberTexArr[0]->SetTexture(std::to_string((score / 10000) % 10));
	}
}