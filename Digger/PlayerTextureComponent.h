#pragma once
#include "Component.h"
#include "Observer.h"

namespace FH
{
	class TextureComponent;
	class PlayerComponent;
	class LiveTextureComponent;

	class PlayerTextureComponent : public Component, public Observer
	{
	public:
		PlayerTextureComponent(GameObject* pOwner, PlayerComponent* pPlayer);
		virtual ~PlayerTextureComponent() = default;
		PlayerTextureComponent(const PlayerTextureComponent& other) = delete;
		PlayerTextureComponent(PlayerTextureComponent&& other) = delete;
		PlayerTextureComponent& operator=(const PlayerTextureComponent& other) = delete;
		PlayerTextureComponent& operator=(PlayerTextureComponent&& other) = delete;

		void OnNotify(GameObject* go, GameEvent e) override;

	private:
		LiveTextureComponent* m_MoveLeftTex{};
		LiveTextureComponent* m_MoveRightTex{};
		LiveTextureComponent* m_MoveUpTex{};
		LiveTextureComponent* m_MoveDownTex{};

		TextureComponent* m_DeadTex{};
	};
}
