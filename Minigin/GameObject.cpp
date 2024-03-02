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

void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

int GameObject::AddComponent(Component* pComponent)
{
	auto uniqueComp{ std::unique_ptr<Component>(pComponent) };
	return AddComponent(std::move(uniqueComp));
}

int GameObject::AddComponent(std::unique_ptr<Component> pComponent)
{
	if (m_CurrentHash >= INT32_MAX)
		throw MaxComponentsReachedException();

	m_pComponents.emplace_back(std::move(pComponent));

	return m_CurrentHash++;
}

bool GameObject::CheckComponent(std::unique_ptr<Component> pComponent)
{
	return CheckComponent(pComponent->GetComponentIdx());
}

bool GameObject::CheckComponent(int idx)
{
	if (m_pComponents[idx] == nullptr)
	{
		return false;
	}
	return true;
}

Component* GameObject::GetComponentWithIdx(int idx)
{
	if (!CheckComponent(idx))
		throw ComponentIdxOutOfRangeException();
	
	return m_pComponents[idx].get();
}

void GameObject::ClearComponentWithIdx(int idx)
{
	if (!CheckComponent(idx))
		throw ComponentIdxOutOfRangeException();

	m_pComponents.erase(m_pComponents.begin() + idx);
}

void GameObject::ClearAllComponents()
{
	m_pComponents.clear();
}