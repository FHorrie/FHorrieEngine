#include "SceneManager.h"
#include "Scene.h"

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

FH::Scene& FH::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
