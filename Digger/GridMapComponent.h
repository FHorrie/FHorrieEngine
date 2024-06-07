#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "Component.h"
#include "GeoStructs.h"
#include "GeoUtils.h"

namespace FH
{
	struct Cell
	{
		utils::Rect m_Rect{};
		glm::vec2 m_Center{};

		bool m_HasGem = false;
		bool m_HasBag = false;
		bool m_HasPlayer = false;
		bool m_IsVisited = false;
	};

	class GridMapComponent final : public Component
	{
	public:
		void Render() const override;

		GridMapComponent(GameObject* pOwner, int rows, int cols,
			float leftGrace = 0.f, float rightGrace = 0.f, float topGrace = 0.f, float bottomGrace = 0.f);
		GridMapComponent(GameObject* pOwner, int rows, int cols, utils::Color4f gridColor,
			float leftGrace = 0.f, float rightGrace = 0.f, float topGrace = 0.f, float bottomGrace = 0.f);
		virtual ~GridMapComponent() = default;
		GridMapComponent(const GridMapComponent& other) = delete;
		GridMapComponent(GridMapComponent&& other) = delete;
		GridMapComponent& operator=(const GridMapComponent& other) = delete;
		GridMapComponent& operator=(GridMapComponent&& other) = delete;

		int GetAmtRows() const { return m_CellRows; }
		int GetAmtCols() const { return m_CellCols; }

		Cell* GetCell(int idx) const 
			{ return m_Cells[idx].get(); }
		void SetCellVisited(int idx) 
			{ m_Cells[idx]->m_IsVisited = true; }

	private:
		int m_CellRows{};
		int m_CellCols{};

		float m_CellWidth{};
		float m_CellHeight{};

		float m_LeftGrace{};
		float m_RightGrace{};
		float m_TopGrace{};
		float m_BottomGrace{};

		SDL_Renderer* m_Renderer{};

		std::vector<std::unique_ptr<Cell>> m_Cells{};

		utils::Color4f m_GridColor {200, 100, 0};
	};
}

