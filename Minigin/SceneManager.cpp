#include "SceneManager.h"
#include "GameObject.h"

#include <algorithm>

void FH::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void FH::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void FH::SceneManager::RenderUI()
{
	for (const auto& scene : m_scenes)
	{
		scene->RenderUI();
	}
}

FH::SceneManager::Scene* FH::SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::make_unique<Scene>(name);
	auto* rawPtr = scene.get();

	m_scenes.push_back(std::move(scene));


	return rawPtr;
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
