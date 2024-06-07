#pragma once
#include "Component.h"
#include "GeoStructs.h"

namespace FH
{
	struct Cell;
	class PlayerComponent;
	class TextureComponent;
	class GridMapComponent;
	class GemComponent : public Component
	{
	public:
		GemComponent(GameObject* pOwner, int col, int row, 
			GridMapComponent* pGridMap, PlayerComponent* pPlayer);
		virtual ~GemComponent() = default;
		GemComponent(const GemComponent& other) = delete;
		GemComponent(GemComponent&& other) = delete;
		GemComponent& operator=(const GemComponent& other) = delete;
		GemComponent& operator=(GemComponent&& other) = delete;

		void Update() override;

		Cell* GetCurrentCell() { return m_Cell; }

	private:
		Cell* m_Cell{};
		bool m_PickedUp{};

		utils::Rect m_HitBox{ 0,0,16,16 };

		TextureComponent* m_GemTex{};
		PlayerComponent* m_pPlayer{};
	};
}



