#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include "Component.h"

namespace FH
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::unique_ptr<GameObject> pObject);
		void Remove(std::unique_ptr<GameObject> pObject);
		void RemoveAll();

		void Update();
		void Render() const;
		void RenderUI();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_pObjects{};

		static unsigned int m_idCounter; 
	};

}
