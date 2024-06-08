#pragma once
#include <glm/vec2.hpp>

#include "CoinBagStates.h"
#include "Component.h"
#include "GeoStructs.h"
#include "Subject.h"

namespace FH
{
	struct Cell;
	class GridMapComponent;
	class PlayerComponent;
	class CoinBagComponent : public Component, public Subject
	{
	public:
		CoinBagComponent(GameObject* pOwner, int col, int row, 
			GridMapComponent* pGridMap, PlayerComponent* pPlayer);
		virtual ~CoinBagComponent() = default;
		CoinBagComponent(const CoinBagComponent& other) = delete;
		CoinBagComponent(CoinBagComponent&& other) = delete;
		CoinBagComponent& operator=(const CoinBagComponent& other) = delete;
		CoinBagComponent& operator=(CoinBagComponent&& other) = delete;

		void Update() override;
		void UpdatePos();

		void SetState(std::unique_ptr<CoinBagState> state) { m_State = std::move(state); };
		void StateNotify(GameEvent e) { Notify(GetOwner(), e); }

		Cell* GetCurrentCell();
		Cell* GetNextCellDown();
		void SetNewCellTarget(int col, int row);

		utils::Rect GetHitBox() const { return m_HitBox; }
		PlayerComponent* GetPlayer() const { return m_pPlayer; }
		int GetCurrentCol() const { return m_CurrentCol; }
		int GetCurrentRow() const { return m_CurrentRow; }

		bool IsMoving() const { return m_IsMoving; }

	private:

		glm::vec2 m_PreviousPos{};
		glm::vec2 m_CurrentPos{};
		glm::vec2 m_DesiredPos{};
		float m_LerpFactor{};
		const float m_LerpSpeed{ 3.f };
		bool m_IsMoving{};

		utils::Rect m_HitBox{ 0,0,16,16 };
		int m_CurrentCol{};
		int m_CurrentRow{};

		std::unique_ptr<CoinBagState> m_State{ std::make_unique<IdleBagState>() };

		GridMapComponent* m_pGridMap{};
		PlayerComponent* m_pPlayer{};
	};
}

