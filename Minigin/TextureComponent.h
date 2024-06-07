#pragma once
#include "Component.h"
#include "Transform.h"

#include <string>

namespace FH 
{
	class Texture2D;
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(GameObject* pOwner, bool hide = false);
		TextureComponent(
			GameObject* pOwner, const std::string& mapIdentifier, bool hide = false);
		TextureComponent(
			GameObject* pOwner, const std::string& mapIdentifier,
			float x, float y, bool hide = false);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Render() const override;

		void SetTexture(const std::string& mapIdentifier);
		void SetPosition(float x, float y) { m_Translate = glm::vec3(x, y, 0.0f); }
		void SetHidden(bool hidden) { m_Hidden = hidden; }

	private:
		glm::vec3 m_Translate{};
		Texture2D* m_Texture{ nullptr };

		bool m_Hidden{};
	};
}