#include "TextureComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"

using namespace FH;

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
	m_Translate = glm::vec3(x, y, 0.f);
}

void TextureComponent::Render() const
{
	const auto& pos = m_Translate + GetParentTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void TextureComponent::SetPosition(float x, float y)
{
	m_Translate = glm::vec3(x, y, 0.0f);
}