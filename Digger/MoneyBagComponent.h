#pragma once
#include <SDL.h>

#include "MoneyBagStates.h"
#include "Component.h"
#include "GeoStructs.h"
#include "glm/vec2.hpp"
#include "GridMapComponent.h"

namespace FH
{
	class PlayerComponent;
	class MoneyBagComponent : public Component
	{
	public:
		MoneyBagComponent(GameObject* pOwner, int col, int row, GridMapComponent* pGridMap, PlayerComponent* pPlayer);
		virtual ~MoneyBagComponent() = default;
		MoneyBagComponent(const MoneyBagComponent& other) = delete;
		MoneyBagComponent(MoneyBagComponent&& other) = delete;
		MoneyBagComponent& operator=(const MoneyBagComponent& other) = delete;
		MoneyBagComponent& operator=(MoneyBagComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		void SetState(std::unique_ptr<MoneyBagState> state) { m_State = std::move(state); };

		void UpdatePos();
		Cell GetNextCellDown();
		void SetNewCellTarget(int col, int row);

		void SetPickedUp() { m_IsPickedUp = true; }
		bool IsPickedUp() { return m_IsPickedUp; }

		utils::Rect GetHitBox() const { return m_HitBox; }
		PlayerComponent* GetPlayer() const;
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
		bool m_IsPickedUp{};
		int m_CurrentCol{};
		int m_CurrentRow{};

		std::unique_ptr<MoneyBagState> m_State{ std::make_unique<IdleBagState>() };

		SDL_Renderer* m_pRenderer{};
		GridMapComponent* m_pGridMap{};
		PlayerComponent* m_pPlayer{};
	};
}

