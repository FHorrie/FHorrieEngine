#include "CoinBagTextureComponent.h"
#include "GameObject.h"
#include "CoinBagComponent.h"
#include "TextureComponent.h"
#include "LiveTextureComponent.h"

FH::CoinBagTextureComponent::CoinBagTextureComponent(GameObject* pOwner, CoinBagComponent* pCoinBag)
	: Component(pOwner)
{
	m_BagIdleTex = static_cast<TextureComponent*>
		(pOwner->AddComponent(std::make_unique<TextureComponent>(pOwner, false)).pComponent);

	m_BagFallingTex = static_cast<TextureComponent*>
		(pOwner->AddComponent(std::make_unique<TextureComponent>(pOwner, true)).pComponent);

	m_BagWiggleTex = static_cast<LiveTextureComponent*>
		(pOwner->AddComponent(std::make_unique<LiveTextureComponent>(pOwner, 0.1f, true)).pComponent);

	m_BagBrokenTex = static_cast<LiveTextureComponent*>
		(pOwner->AddComponent(std::make_unique<LiveTextureComponent>(pOwner, 0.1f, true)).pComponent);
	m_BagBrokenTex->SetLoop(false);

	m_BagIdleTex->SetTexture("IdleBag");
	m_BagFallingTex->SetTexture("FallingBag");

	m_BagWiggleTex->AddSprites({ "LeftBag", "IdleBag", "RightBag", "IdleBag" });
	m_BagBrokenTex->AddSprites({ "IdleBag", "Gold1", "Gold2", "Gold3" });

	pCoinBag->AddObserver(this);
}

void FH::CoinBagTextureComponent::OnNotify(GameObject* go, GameEvent e)
{
	go;

	switch (e)
	{
	case GameEvent::EVENT_BAG_WIGGLE:
		m_BagIdleTex->SetHidden(true);
		m_BagWiggleTex->SetHidden(false);
		break;
	case GameEvent::EVENT_BAG_FALL:
		m_BagWiggleTex->SetHidden(true);
		m_BagFallingTex->SetHidden(false);
		break;
	case GameEvent::EVENT_BAG_BREAK:
		m_BagFallingTex->SetHidden(true);
		m_BagBrokenTex->SetHidden(false);
		break;
	case GameEvent::EVENT_BAG_PICKUP:
		m_BagBrokenTex->SetHidden(true);
	default:
		break;
	}
}