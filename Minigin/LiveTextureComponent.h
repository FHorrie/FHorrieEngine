#pragma once
#include "Component.h"
#include "Transform.h"

#include <string>
#include <vector>

namespace FH
{
	class Texture2D;
	class LiveTextureComponent final : public Component
	{
	public:
		LiveTextureComponent(GameObject* pOwner, bool hide = false);
		LiveTextureComponent(GameObject* pOwner, float spriteTime, bool hide = false);
		virtual ~LiveTextureComponent() = default;
		LiveTextureComponent(const LiveTextureComponent& other) = delete;
		LiveTextureComponent(LiveTextureComponent&& other) = delete;
		LiveTextureComponent& operator=(const LiveTextureComponent& other) = delete;
		LiveTextureComponent& operator=(LiveTextureComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		void AddSprite(const std::string& mapIdentifier);
		void AddSprites(const std::vector<std::string>& mapIdentifiers);
		void SetSpriteDisplayTime(float maxDisplayTime) { m_MaxTime = maxDisplayTime; }
		void SetPosition(float x, float y) { m_Translate = glm::vec3(x, y, 0.0f); }
		void SetLoop(bool loop) { m_ShouldLoop = loop; }
		void SetHidden(bool hidden);

	private:
		glm::vec3 m_Translate{};
		std::vector<Texture2D*> m_SpriteVec{};

		int m_CurrentSpriteIndex{};
		int m_MaxSpriteIndex{};
		float m_AccuTime{};
		float m_MaxTime{0.1f};

		bool m_Hidden{};
		bool m_ShouldLoop{ true };
		bool m_WillLoop{ true };
	};
}
	

