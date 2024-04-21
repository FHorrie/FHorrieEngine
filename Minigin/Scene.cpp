#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

unsigned int FH::Scene::m_idCounter = 0;

FH::Scene::Scene(const std::string& name) : m_name(name) {}

FH::Scene::~Scene() = default;

void FH::Scene::Add(std::unique_ptr<GameObject> pObject)
{
	m_pObjects.emplace_back(std::move(pObject));
}

void FH::Scene::Remove(std::unique_ptr<GameObject> pObject)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), pObject), m_pObjects.end());
}

void FH::Scene::RemoveAll()
{
	m_pObjects.clear();
}

void FH::Scene::Update()
{
	for(auto& object : m_pObjects)
	{
		object->Update();
	}
}

void FH::Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

void FH::Scene::RenderUI()
{
	for (const auto& object : m_pObjects)
	{
		object->RenderUI();
	}
}