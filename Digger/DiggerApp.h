#pragma once
#include "Scene.h"
#include "GridMapComponent.h"
#include "GeoStructs.h"

namespace FH
{
	class GameObject;
	class DiggerApp final
	{
	public:
		DiggerApp() = default;
		~DiggerApp() = default;
		DiggerApp(const DiggerApp&) = delete;
		DiggerApp(DiggerApp&&) = default;
		DiggerApp& operator=(const DiggerApp&) = delete;
		DiggerApp& operator=(DiggerApp&&) = default;

		void Run();

	private:
		void MakeDiggerGame();
		void CreateLevel(std::string levelPath);

		GenData ParseLevelFile(std::string levelPath);

		void MapControls(GameObject* controlledObj, GridMapComponent* pMap, 
			bool useKeyboard = false, int controllerIdx = 0);

		void LoadTextures();
		void LoadSounds();

		int m_LevelIdx{};

		static constexpr int COLORAMOUNT{ 4 };

		const utils::Color4f mapColors[COLORAMOUNT]{
			utils::Color4f(255, 200, 50), 
			utils::Color4f(100, 200, 100),
			utils::Color4f(200, 50, 50),
			utils::Color4f(100, 200, 50)
		};

	};
}


