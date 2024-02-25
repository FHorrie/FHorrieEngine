#include <string>
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace dae;

GameObject::~GameObject()
{

}

void GameObject::Update()
{
	for (auto& pComp : m_pComponents)
	{
		pComp->Update();
	}
}

void GameObject::Render() const
{
	for (auto& pComp : m_pComponents)
	{
		pComp->Render();
	}
}

//void GameObject::SetTexture(const std::string& filename)
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

int GameObject::AddComponent(std::shared_ptr<Component> pComponent)
{
	if (m_ComponentAmount >= INT32_MAX)
		throw MaxComponentsReachedException();

	m_pComponents.emplace_back(pComponent);
	m_ComponentAmount++;

	return static_cast<int>(m_pComponents.size() - 1);
}

bool GameObject::CheckComponent(std::shared_ptr<Component> pComponent)
{
	if (std::ranges::find(m_pComponents, pComponent) == m_pComponents.cend())
	{
		return false;
	}
	return true;
}

std::shared_ptr<Component> GameObject::GetComponentWithIdx(int idx)
{
	if (idx < m_ComponentAmount)
		return m_pComponents[idx];
	else
		throw ComponentIdxOutOfRangeException();
}

void GameObject::ClearComponentWithIdx(int idx)
{
	if (idx >= m_ComponentAmount)
		throw ComponentIdxOutOfRangeException();

	const auto componentIt{ m_pComponents.begin() + idx };

	m_pComponents.erase(componentIt);
	m_ComponentAmount--;
}

void GameObject::ClearAllComponents()
{
	m_pComponents.clear();
	m_ComponentAmount = 0;
}