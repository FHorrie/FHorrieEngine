#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace dae;

TextureComponent::TextureComponent(GameObject* pOwner)
	: Component(pOwner)
{}

TextureComponent::TextureComponent(GameObject* pOwner, const std::string& filename)
	: Component(pOwner)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

TextureComponent::TextureComponent(GameObject* pOwner, const std::string& filename, float x, float y)
	: Component(pOwner)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	m_LocalTransform.SetPosition(x, y, 0.f);
}

void TextureComponent::Render() const
{
	const auto& pos = (m_LocalTransform.GetPosition() + GetParentTransform().GetPosition());
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::SetPosition(float x, float y)
{
	m_LocalTransform.SetPosition(x, y, 0.0f);
}