#pragma once
#include "Component.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae 
{
	class TextureComponent final : public Component
	{
	public:
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		TextureComponent(GameObject* pOwner);
		TextureComponent(GameObject* pOwner, const std::string& filename);
		TextureComponent(GameObject* pOwner, const std::string& filename, float x, float y);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		Transform m_LocalTransform{};
		std::shared_ptr<Texture2D> m_Texture{ nullptr };
	};
}

