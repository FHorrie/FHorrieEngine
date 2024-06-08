#pragma once
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
		PlayerComponent(GameObject* pOwner, GridMapComponent* gridMap);
		PlayerComponent(GameObject* pOwner, int col, int row, GridMapComponent* gridMap);
		PlayerComponent(GameObject* pOwner, int col, int row, int lives, GridMapComponent* gridMap);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Update() override;

		void UpdatePos();
		void SetNewCellTarget(int col, int row);
		void SetCellPos(int col, int row);

		void GainPoints(PointType type);
		void GainGemReward();
		void UpdateGemReward();
		void DefaultAttack();
		void UpdateAttackTime();
		void Die();
		void Respawn();

		utils::Rect GetHitBox() const { return m_HitBox; }
		int GetCurrentCol() const { return m_CurrentCol; }
		int GetCurrentRow() const { return m_CurrentRow; }
		int GetColDirection() const { return m_ColDir; }
		int GetRowDirection() const { return m_RowDir; }
		Cell* GetCurrentCell();

		int GetScore() const { return m_Score; }
		int GetLives() const { return m_Lives; }
		bool IsMoving() const { return m_IsMoving; }
		bool IsDead() const { return m_IsDead; }

	private:
		glm::vec2 m_PreviousPos{};
		glm::vec2 m_CurrentPos{};
		glm::vec2 m_DesiredPos{};
		float m_LerpFactor{};
		float m_LerpSpeed{1.f};
		bool m_IsMoving{};

		utils::Rect m_HitBox{ 0,0,16,16 };

		int m_RespawnCol{};
		int m_RespawnRow{};

		int m_CurrentCol{};
		int m_CurrentRow{};

		int m_ColDir{-1};
		int m_RowDir{};

		inline static int m_Score{};

		int m_GemStreak{};
		float m_GemTime{ 2.f };
		float m_AccuGemTime{};

		const float m_AttackTime{ 2.f };
		float m_AccuAttackTime{};

		const float m_RespawnTime{ 5.f };
		float m_AccuRespawnTime{};

		inline static int m_Lives{ 4 };
		bool m_IsDead{};
	
		GridMapComponent* m_pGridMap{};
	};
}

