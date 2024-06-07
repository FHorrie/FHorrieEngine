#pragma once
#include <SDL.h>
#include <glm/vec2.hpp>

#include "Component.h"
#include "Subject.h"
#include "GeoStructs.h"

namespace FH
{
	enum class PointType
	{
		GemType,
		CoinType,
		EnemyKillType
	};

	class GridMapComponent;
	struct Cell;
	class PlayerComponent : public Component, public Subject
	{
	public:
		PlayerComponent(GameObject* pOwner, int col, int row, GridMapComponent* gridMap);
		PlayerComponent(GameObject* pOwner, int col, int row, int lives, GridMapComponent* gridMap);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		void UpdatePos();
		void SetNewCellTarget(int col, int row);

		void GainPoints(PointType type);
		void GainGemReward();
		void UpdateGemReward();
		void DefaultAttack(GameObject* Target);
		void TakeDamage(int damage);

		utils::Rect GetHitBox() const { return m_HitBox; }
		int GetCurrentCol() const { return m_CurrentCol; }
		int GetCurrentRow() const { return m_CurrentRow; }
		int GetPreviousCol() const { return m_PreviousCol; }
		int GetPreviousRow() const { return m_PreviousRow; }
		Cell* GetCurrentCell();

		int GetScore() const { return m_Score; }
		int GetLives() const { return m_Lives; }
		bool IsDead() const { return m_IsDead; }
		bool IsMoving() const { return m_IsMoving; }


	private:
		glm::vec2 m_PreviousPos{};
		glm::vec2 m_CurrentPos{};
		glm::vec2 m_DesiredPos{};
		float m_LerpFactor{};
		float m_LerpSpeed{1.f};
		bool m_IsMoving{};

		utils::Rect m_HitBox{ 0,0,16,16 };

		int m_PreviousCol{};
		int m_PreviousRow{};
		int m_CurrentCol{};
		int m_CurrentRow{};

		int m_Score{};
		int m_GemStreak{};
		float m_GemTime{ 2.f };
		float m_AccuGemTime{};

		int m_Lives{ 3 };
		bool m_IsDead{};
	
		SDL_Renderer* m_pRenderer{};
		GridMapComponent* m_pGridMap{};
	};
}

