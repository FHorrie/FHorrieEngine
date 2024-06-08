#include "GridMapComponent.h"
#include "Minigin.h"
#include "Renderer.h"

FH::GridMapComponent::GridMapComponent(GameObject* pOwner, GenData genData,
	float leftGrace, float rightGrace, float topGrace, float bottomGrace)
	: Component(pOwner)
	, m_CellRows{ genData.mapRows }
	, m_CellCols{ genData.mapCols }
	, m_LeftGrace{ leftGrace }
	, m_RightGrace{ rightGrace }
	, m_TopGrace{ topGrace }
	, m_BottomGrace{ bottomGrace }
{
	m_Renderer = Renderer::GetInstance().GetSDLRenderer();

	constexpr int gameWidth{ Renderer::GetLogicalWidth() };
	constexpr int gameHeight{ Renderer::GetLogicalHeight() };

	const float freeWidth{ gameWidth - m_LeftGrace - m_RightGrace };
	const float freeHeight{ gameHeight - m_TopGrace - m_BottomGrace };

	m_FullWidth = gameWidth;
	m_FullHeight = gameHeight - m_TopGrace;

	m_CellWidth = freeWidth / m_CellCols;
	m_CellHeight = freeHeight / m_CellRows;

	for(int row{}; row < m_CellRows; ++row)
		for (int col{}; col < m_CellCols; ++col)
		{
			float left{ m_LeftGrace + m_CellWidth * col };
			float bottom{ m_TopGrace + m_CellHeight * row }; //Y axis is from top to bottom

			utils::Rect cellRect{ left, bottom, m_CellWidth, m_CellHeight };
			glm::vec2 cellCenter{ left + m_CellWidth / 2, bottom + m_CellHeight / 2 };
			m_Cells.emplace_back(std::make_unique<Cell>(row, col, cellRect, cellCenter));
		}

	for (int row{}; row < m_CellRows; ++row)
		for (int col{}; col < m_CellCols; ++col)
		{
			const int idx{ col + row * m_CellCols };

			switch (genData.mapData[idx])
			{
			case 0:
				break;
			case 1:
				m_Cells[idx]->m_IsVisited = true;
				break;
			case 2:
				m_Cells[idx]->m_HasBag = true;
				break;
			case 3:
				m_Cells[idx]->m_HasGem = true;
				break;
			case 4:
				m_Cells[idx]->m_HasPlayer = true;
				break;
			default:
				break;
			}
		}
}

FH::GridMapComponent::GridMapComponent(GameObject* pOwner, GenData genData, utils::Color4f gridColor,
	float leftGrace, float rightGrace, float topGrace, float bottomGrace)
	: GridMapComponent(pOwner, genData, leftGrace, rightGrace, topGrace, bottomGrace)
{
	m_GridColor = gridColor;
}

void FH::GridMapComponent::Render() const
{
	utils::RectFunctions::DrawFillRect(m_Renderer, utils::Rect(0, m_TopGrace, m_FullWidth, m_FullHeight), m_GridColor);
	for (const auto& cell : m_Cells)
	{
		if(cell->m_IsVisited)
			utils::RectFunctions::DrawFillRect(m_Renderer, cell->m_Rect, BLACK);
	}
}
