#pragma once
#include "Component.h"
#include "GeoStructs.h"

namespace FH
{
	struct Cell;
	class PlayerComponent;
	class LiveTextureComponent;
	class GridMapComponent;
	class ProjectileComponent : public Component
	{
	public:
		ProjectileComponent(GameObject* pOwner, int col, int row, glm::vec2 dir,
			GridMapComponent* pGridMap, PlayerComponent* pPlayer);
		virtual ~ProjectileComponent() = default;
		ProjectileComponent(const ProjectileComponent& other) = delete;
		ProjectileComponent(ProjectileComponent&& other) = delete;
		ProjectileComponent& operator=(const ProjectileComponent& other) = delete;
		ProjectileComponent& operator=(ProjectileComponent&& other) = delete;

		void Update() override;

	private:
		void UpdatePos();
		void CheckPath();
		void DestroyBall();
		void SetNewCellTarget(int col, int row, bool willBreak = false);
		Cell* GetCell(int colDir = 0, int rowDir = 0);

		glm::vec2 m_PreviousPos{};
		glm::vec2 m_CurrentPos{};
		glm::vec2 m_DesiredPos{};

		float m_LerpFactor{};
		const float m_LerpSpeed{ 5.f };
		bool m_IsMoving{};

		int m_CurrentCol{};
		int m_CurrentRow{};

		int m_ColDir{};
		int m_RowDir{};
		bool m_WillBreak{};
		bool m_Broken{};

		utils::Rect m_HitBox{ 0,0,8,8 };

		LiveTextureComponent* m_ProjectileTex{};

		GridMapComponent* m_pGridMap{};
		PlayerComponent* m_pPlayer{};
	};
}

