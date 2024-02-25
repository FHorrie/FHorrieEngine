#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace dae;

TextureComponent::TextureComponent(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::Update() {}

void TextureComponent::Render() const
{
	const auto& pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}