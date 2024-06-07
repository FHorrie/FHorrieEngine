#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "Singleton.h"
#include "Texture2D.h"
#include "Font.h"

namespace FH
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		Texture2D* LoadTexture(
			const std::string& file, const std::string& mapIdentifier);
		Font* LoadFont(
			const std::string& file, unsigned int size, const std::string& mapIdentifier);

		Texture2D* GetTexture(const std::string& mapIdentifier);
		Font* GetFont(const std::string& mapIdentifier);

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;

		std::unordered_map
			<std::string, std::unique_ptr<Font>> m_FontMap;
		std::unordered_map
			<std::string, std::unique_ptr<Texture2D>> m_TextureMap;
	};
}
