#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace FH;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> pObject)
{
	m_pObjects.emplace_back(std::move(pObject));
}

void Scene::Remove(std::unique_ptr<GameObject> pObject)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), pObject), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

void Scene::Update()
{
	for(auto& object : m_pObjects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

void Scene::RenderUI()
{
	for (const auto& object : m_pObjects)
	{
		object->RenderUI();
	}
}