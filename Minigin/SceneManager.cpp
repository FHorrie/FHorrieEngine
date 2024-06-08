#include "SceneManager.h"
#include "GameObject.h"

#include <algorithm>
#include <iostream>
#include <format>

void FH::SceneManager::Update()
{
	m_Scenes[m_ActiveSceneIdx]->Update();
}

void FH::SceneManager::Render()
{
	m_Scenes[m_ActiveSceneIdx]->Render();
}

void FH::SceneManager::RenderUI()
{
	m_Scenes[m_ActiveSceneIdx]->RenderUI();
}

FH::SceneManager::Scene* FH::SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::make_unique<Scene>(name);
	auto* rawPtr = scene.get();

	m_Scenes.push_back(std::move(scene));


	return rawPtr;
}

void FH::SceneManager::SwitchScenes(int idx)
{
	if (idx >= 0 && idx < GetSceneCount())
		m_ActiveSceneIdx = idx;
	else
		std::cerr << std::format("Scene with index {} does not exist", idx) << std::endl;
}

void FH::SceneManager::GoToNextScene()
{
	if (m_ActiveSceneIdx < GetSceneCount() - 1)
		++m_ActiveSceneIdx;
	else
	{
		std::cout << "Final scene reached, use 'F3' to go back to scene 1" << std::endl;
	}
}

void FH::SceneManager::GoToStartScene()
{
	m_ActiveSceneIdx = 0;
}

void FH::SceneManager::Scene::Add(std::unique_ptr<GameObject> pObject)
{
	m_pObjects.emplace_back(std::move(pObject));
}

void FH::SceneManager::Scene::Remove(std::unique_ptr<GameObject> pObject)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), pObject), m_pObjects.end());
}

void FH::SceneManager::Scene::RemoveAll()
{
	m_pObjects.clear();
}

void FH::SceneManager::Scene::Update()
{
	for (auto& object : m_pObjects)
	{
		object->Update();
	}
}

void FH::SceneManager::Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

void FH::SceneManager::Scene::RenderUI()
{
	for (const auto& object : m_pObjects)
	{
		object->RenderUI();
	}
}
