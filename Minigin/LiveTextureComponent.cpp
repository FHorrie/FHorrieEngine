#include "LiveTextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "FHTime.h"

FH::LiveTextureComponent::LiveTextureComponent(GameObject* pOwner, bool hide)
	: Component(pOwner)
	, m_Hidden{ hide }
{}

FH::LiveTextureComponent::LiveTextureComponent(GameObject* pOwner, float spriteTime, bool hide)
	: Component(pOwner)
	, m_MaxTime{ spriteTime }
	, m_Hidden{ hide }
{}

void FH::LiveTextureComponent::Update()
{
	if (m_Hidden || !m_WillLoop)
		return;

	if (m_AccuTime < m_MaxTime)
	{
		m_AccuTime += Time::GetDeltaTime();
		return;
	}

	++m_CurrentSpriteIndex;
	if (m_CurrentSpriteIndex >= m_MaxSpriteIndex)
	{
		if (!m_ShouldLoop)
		{
			m_WillLoop = false;
			m_CurrentSpriteIndex = m_MaxSpriteIndex - 1;
		}
		else
			m_CurrentSpriteIndex = 0;
	}

	m_AccuTime = 0.f;
}

void FH::LiveTextureComponent::Render() const
{
	const auto& pos = m_Translate + GetParentTransform().GetPosition();
	if (!m_SpriteVec.empty() && !m_Hidden)
		Renderer::GetInstance().RenderTexture(*m_SpriteVec[m_CurrentSpriteIndex], pos.x, pos.y);
}

void FH::LiveTextureComponent::AddSprite(const std::string& mapIdentifier)
{
	auto* texture{ ResourceManager::GetInstance().GetTexture(mapIdentifier) };

	if (texture)
	{
		m_SpriteVec.push_back(texture);
		m_MaxSpriteIndex = static_cast<int>(m_SpriteVec.size());
	}
}

void FH::LiveTextureComponent::AddSprites(const std::vector<std::string>& mapIdentifiers)
{
	for (const auto& mapIdentifier : mapIdentifiers)
		AddSprite(mapIdentifier);
}

void FH::LiveTextureComponent::SetHidden(bool hidden)
{
	m_Hidden = hidden;
	m_CurrentSpriteIndex = 0;
	m_AccuTime = 0.f;
	m_WillLoop = true;
}