#include <iostream>

#include "TextureComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"

using namespace FH;

TextureComponent::TextureComponent(GameObject* pOwner, bool hide)
	: Component(pOwner)
	, m_Hidden{ hide }
{}

TextureComponent::TextureComponent(
	GameObject* pOwner, const std::string& mapIdentifier, bool hide)
	: Component(pOwner)
	, m_Hidden{ hide }
{
	SetTexture(mapIdentifier);
}

TextureComponent::TextureComponent(
	GameObject* pOwner, const std::string& mapIdentifier, float x, float y, bool hide)
	: Component(pOwner)
	, m_Translate{ glm::vec3(x, y, 0.f) }
	, m_Hidden{ hide }
{
	m_Texture = ResourceManager::GetInstance().GetTexture(mapIdentifier);
}

void TextureComponent::Render() const
{
	const auto& pos = m_Translate + GetParentTransform().GetPosition();
	if(m_Texture && !m_Hidden)
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void TextureComponent::SetTexture(const std::string& mapIdentifier)
{
	auto texture = ResourceManager::GetInstance().GetTexture(mapIdentifier);
	if (texture == nullptr)
	{
		std::cerr << "Could not find Texture in Loaded Resources, make sure the texture is loaded!" 
			<< std::endl;
	}
	//Assign new pointer even if nullptr (the user does not want the old one anymore)
	m_Texture = texture;
}