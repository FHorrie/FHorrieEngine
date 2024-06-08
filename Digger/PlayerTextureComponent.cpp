#include "PlayerTextureComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"
#include "LiveTextureComponent.h"

FH::PlayerTextureComponent::PlayerTextureComponent(GameObject* pOwner, PlayerComponent* pPlayer)
	: Component(pOwner)
{
	m_MoveLeftTex = static_cast<LiveTextureComponent*>
		(pOwner->AddComponent(std::make_unique<LiveTextureComponent>(pOwner, 0.1f)).pComponent);

	m_MoveRightTex = static_cast<LiveTextureComponent*>
		(pOwner->AddComponent(std::make_unique<LiveTextureComponent>(pOwner, 0.1f, true)).pComponent);

	m_MoveUpTex = static_cast<LiveTextureComponent*>
		(pOwner->AddComponent(std::make_unique<LiveTextureComponent>(pOwner, 0.1f, true)).pComponent);

	m_MoveDownTex = static_cast<LiveTextureComponent*>
		(pOwner->AddComponent(std::make_unique<LiveTextureComponent>(pOwner, 0.1f, true)).pComponent);

	m_DeadTex = static_cast<TextureComponent*>
		(pOwner->AddComponent(std::make_unique<TextureComponent>(pOwner, true)).pComponent);

	m_GraveStoneTex = static_cast<LiveTextureComponent*>
		(pOwner->AddComponent(std::make_unique<LiveTextureComponent>(pOwner, 0.25f, true)).pComponent);
	m_GraveStoneTex->SetLoop(false);


	m_MoveLeftTex->AddSprites({ "LeftDig1", "LeftDig2", "LeftDig3", "LeftDig2" });
	m_MoveRightTex->AddSprites({ "RightDig1", "RightDig2", "RightDig3", "RightDig2" });
	m_MoveUpTex->AddSprites({ "UpDig1", "UpDig2", "UpDig3", "UpDig2" });
	m_MoveDownTex->AddSprites({ "DownDig1", "DownDig2", "DownDig3", "DownDig2" });

	m_DeadTex->SetTexture("DeadDig");
	m_GraveStoneTex->AddSprites({ "Grave1", "Grave2", "Grave3", "Grave4", "Grave5" });

	pPlayer->AddObserver(this);
}

void FH::PlayerTextureComponent::OnNotify(GameObject* go, GameEvent e)
{
	go;

	switch (e)
	{
	case GameEvent::EVENT_PLAYER_MOVED_LEFT:
		m_MoveLeftTex->SetHidden(false);
		m_MoveRightTex->SetHidden(true);
		m_MoveUpTex->SetHidden(true);
		m_MoveDownTex->SetHidden(true);
		m_DeadTex->SetHidden(true);
		m_GraveStoneTex->SetHidden(true);
		break;
	case GameEvent::EVENT_PLAYER_MOVED_RIGHT:
		m_MoveLeftTex->SetHidden(true);
		m_MoveRightTex->SetHidden(false);
		m_MoveUpTex->SetHidden(true);
		m_MoveDownTex->SetHidden(true);
		m_DeadTex->SetHidden(true);
		m_GraveStoneTex->SetHidden(true);
		break;
	case GameEvent::EVENT_PLAYER_MOVED_UP:
		m_MoveLeftTex->SetHidden(true);
		m_MoveRightTex->SetHidden(true);
		m_MoveUpTex->SetHidden(false);
		m_MoveDownTex->SetHidden(true);
		m_DeadTex->SetHidden(true);
		m_GraveStoneTex->SetHidden(true);
		break;
	case GameEvent::EVENT_PLAYER_MOVED_DOWN:
		m_MoveLeftTex->SetHidden(true);
		m_MoveRightTex->SetHidden(true);
		m_MoveUpTex->SetHidden(true);
		m_MoveDownTex->SetHidden(false);
		m_DeadTex->SetHidden(true);
		m_GraveStoneTex->SetHidden(true);
		break;
	case GameEvent::EVENT_PLAYER_DIED:
		m_MoveLeftTex->SetHidden(true);
		m_MoveRightTex->SetHidden(true);
		m_MoveUpTex->SetHidden(true);
		m_MoveDownTex->SetHidden(true);
		m_DeadTex->SetHidden(false);
		m_GraveStoneTex->SetHidden(false);
		break;
	default:
		break;
	}
}
