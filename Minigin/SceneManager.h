#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Singleton.h"

namespace FH
{
	class GameObject;
	class SceneManager final : public Singleton<SceneManager>
	{
	private:
		class Scene final
		{
		public:
			explicit Scene(const std::string& name) : m_Name(name) {}
			~Scene() = default;
			Scene(const Scene& other) = delete;
			Scene(Scene&& other) = delete;
			Scene& operator=(const Scene& other) = delete;
			Scene& operator=(Scene&& other) = delete;

			void Add(std::unique_ptr<GameObject> pObject);
			void Remove(std::unique_ptr<GameObject> pObject);
			void RemoveAll();

			void Update();
			void Render() const;
			void RenderUI();

		private:
			std::string m_Name;
			std::vector<std::unique_ptr<GameObject>> m_pObjects{};
			
		};

	public:
		Scene* CreateScene(const std::string& name);
		void SwitchScenes(int idx);
		void GoToNextScene();
		int GetSceneCount() { return static_cast<int>(m_Scenes.size()); }
		int GetCurrentSceneIdx() { return m_ActiveSceneIdx; }

		void Update();
		void Render();
		void RenderUI();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_Scenes;
		int m_ActiveSceneIdx{};
	};
}
