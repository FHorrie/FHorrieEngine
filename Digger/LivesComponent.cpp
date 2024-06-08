#include "LivesComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"
#include "ResourceManager.h"

FH::LivesComponent::LivesComponent(GameObject* pOwner, PlayerComponent* pPlayer)
	: Component(pOwner)
	, m_pPlayer{ pPlayer }
{
	for (int i{}; i < LIVESAMT; ++i)
	{
		m_LivesTexArr[i] = static_cast<TextureComponent*>
			(pOwner->AddComponent(std::make_unique<TextureComponent>(pOwner)).pComponent);
		m_LivesTexArr[i]->SetTexture("RightDig1");
		m_LivesTexArr[i]->SetPosition(float(MARGIN + OFFSET + DIGGERSIZE * i), float(MARGIN));
	}

	pPlayer->AddObserver(this);
}

void FH::LivesComponent::OnNotify(GameObject* go, GameEvent e)
{
	go;

	if (e == GameEvent::EVENT_PLAYER_DIED)
	{
		int lives = m_pPlayer->GetLives() - 1;

		if (lives < 0)
			lives = 0;

		for (int i{}; i < LIVESAMT; ++i)
			m_LivesTexArr[i]->SetHidden(true);
		for (int i{}; i < lives; ++i)
			m_LivesTexArr[i]->SetHidden(false);
	}
}