#include "GridMapComponent.h"
#include "Minigin.h"
#include "Renderer.h"

FH::GridMapComponent::GridMapComponent(GameObject* pOwner, int rows, int cols,
	float leftGrace, float rightGrace, float topGrace, float bottomGrace)
	: Component(pOwner)
	, m_CellRows{ rows }
	, m_CellCols{ cols }
	, m_LeftGrace{ leftGrace }
	, m_RightGrace{ rightGrace }
	, m_TopGrace{ topGrace }
	, m_BottomGrace{ bottomGrace }
{
	m_Renderer = Renderer::GetInstance().GetSDLRenderer();

	constexpr int gameWidth{ Renderer::GetLogicalWidth() };
	constexpr int gameHeight{ Renderer::GetLogicalHeight() };

	float freeWidth{ gameWidth - m_LeftGrace - m_RightGrace };
	float freeHeight{ gameHeight - m_TopGrace - m_BottomGrace };

	m_CellWidth = freeWidth / m_CellCols;
	m_CellHeight = freeHeight / m_CellRows;

	for(int row{}; row < m_CellRows; ++row)
		for (int col{}; col < m_CellCols; ++col)
		{
			float left{ m_LeftGrace + m_CellWidth * col };
			float bottom{ m_TopGrace + m_CellHeight * row }; //Y axis is from top to bottom

			utils::Rect cellRect{ left, bottom, m_CellWidth, m_CellHeight };
			glm::vec2 cellCenter{ left + m_CellWidth / 2, bottom + m_CellHeight / 2 };
			m_Cells.emplace_back(std::make_unique<Cell>(cellRect, cellCenter));
		}
}

FH::GridMapComponent::GridMapComponent(GameObject* pOwner, int rows, int cols, utils::Color4f gridColor,
	float leftGrace, float rightGrace, float topGrace, float bottomGrace)
	: GridMapComponent(pOwner, rows, cols, leftGrace, rightGrace, topGrace, bottomGrace)
{
	m_GridColor = gridColor;
}

void FH::GridMapComponent::Render() const
{
	for (const auto& cell : m_Cells)
	{
		if(!cell->m_IsVisited)
			utils::RectFunctions::DrawFillRect(m_Renderer, cell->m_Rect, m_GridColor);
	}
}
