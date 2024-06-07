#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"

void FH::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

FH::Texture2D* FH::ResourceManager::LoadTexture(
	const std::string& file, const std::string& mapIdentifier)
{
	const auto fullPath = m_dataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	auto textureUPtr = std::make_unique<Texture2D>(texture);
	auto rawPtr = textureUPtr.get();
	
	m_TextureMap.insert(std::pair(mapIdentifier, std::move(textureUPtr)));

	return rawPtr;
}

FH::Font* FH::ResourceManager::LoadFont(
	const std::string& file, unsigned int size, const std::string& mapIdentifier)
{
	auto font = std::make_unique<Font>(m_dataPath + file, size);
	auto rawPtr = font.get();

	m_FontMap.insert(std::pair(mapIdentifier, std::move(font)));

	return rawPtr;
}

FH::Texture2D* FH::ResourceManager::GetTexture(const std::string& mapIdentifier)
{
	auto pos = m_TextureMap.find(mapIdentifier);
	if (pos == m_TextureMap.cend())
		return nullptr;
	else
		return pos->second.get();
}

FH::Font* FH::ResourceManager::GetFont(const std::string& mapIdentifier)
{
	auto pos = m_FontMap.find(mapIdentifier);
	if (pos == m_FontMap.cend())
		return nullptr;
	else
		return pos->second.get();
}

