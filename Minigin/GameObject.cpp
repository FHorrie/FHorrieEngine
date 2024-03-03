#include <string>
#include <iostream>

#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace dae;

void GameObject::Update()
{
	UpdateTransform();

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

void GameObject::SetLocalPosition(glm::vec3 pos)
{
	m_Transform.SetPosition(pos);
	m_IsTransformDirty = true;

	for (auto& child : m_pChildren)
		child->SetTransformDirty();
}

void GameObject::UpdateTransform()
{
	if (m_IsTransformDirty)
	{
		if (m_pParent == nullptr)
			m_ParentTransform = Transform();
		else
			m_ParentTransform = m_pParent->GetWorldTransform();
		m_WorldTransform = m_ParentTransform + m_Transform;

		for (auto& comp : m_pComponents)
			comp->SetParentTransform(m_WorldTransform);
	}
	m_IsTransformDirty = false;
}

Transform GameObject::GetWorldTransform()
{
	return m_WorldTransform;
}

#pragma region gameObjectComponentFunctions

int GameObject::AddComponent(Component* pComponent)
{
	auto uniqueComp{ std::unique_ptr<Component>(pComponent) };
	return AddComponent(std::move(uniqueComp));
}

int GameObject::AddComponent(std::unique_ptr<Component> pComponent)
{
	const int currentIdx{ int(m_pComponents.size()) };

	if (currentIdx >= INT32_MAX)
		throw MaxComponentsReachedException();

	m_pComponents.emplace_back(std::move(pComponent));

	return currentIdx;
}

bool GameObject::CheckComponent(std::unique_ptr<Component> pComponent)
{
	if (std::ranges::find(m_pComponents, pComponent) != m_pComponents.cend())
		return CheckComponent(pComponent->GetComponentIdx());
	else return false;
}

bool GameObject::CheckComponent(int idx)
{
	if (int(m_pComponents.size()) < idx)
		return false;
	if (m_pComponents[idx] == nullptr)
		return false;
	return true;
}

Component* GameObject::GetComponentWithIdx(int idx)
{
	if (!CheckComponent(idx))
		throw ComponentOutOfRangeException();
	
	return m_pComponents[idx].get();
}



void GameObject::ClearComponentWithIdx(int idx)
{
	if (!CheckComponent(idx))
		throw ComponentOutOfRangeException();

	m_pComponents.erase(m_pComponents.begin() + idx);
}

void GameObject::ClearAllComponents()
{
	m_pComponents.clear();
}

#pragma endregion

#pragma region gameObjectSceneGraphFunctions

void GameObject::AddChild(std::shared_ptr<GameObject> pObject)
{
	if (pObject->GetChildIdx() != -1)
	{
		pObject->GetParent()->ClearChildWithIdx(pObject->GetChildIdx());
	}

	const int currentChildIdx{ int(m_pChildren.size()) };

	if (currentChildIdx >= INT32_MAX)
		throw MaxChildrenReachedException();

	m_pChildren.emplace_back(pObject);

	pObject->SetParent(this);
	pObject->SetChildIdx(currentChildIdx);
}

bool GameObject::CheckChild(std::shared_ptr<GameObject> pObject)
{
	if (std::ranges::find(m_pChildren, pObject) != m_pChildren.cend())
		return CheckChild(pObject->GetChildIdx());
	else return false;
}

bool GameObject::CheckChild(int idx)
{
	if (int(m_pChildren.size()) < idx)
		return false;
	if (m_pChildren[idx] == nullptr)
		return false;
	return true;
}

GameObject* GameObject::GetChildWithIdx(int idx)
{
	if (!CheckChild(idx))
		throw ChildOutOfRangeException();

	return m_pChildren[idx].get();
}

void GameObject::ClearChild(std::shared_ptr<GameObject> pObject)
{
	const auto childIt = std::ranges::find(m_pChildren, pObject);

	if (childIt == m_pChildren.cend())
		throw ChildOutOfRangeException();

	pObject->SetParent(nullptr);
	pObject->SetChildIdx(-1);

	m_pChildren.erase(childIt);
}

void GameObject::ClearChildWithIdx(int idx)
{
	if (!CheckChild(idx))
		throw ChildOutOfRangeException();

	m_pChildren[idx]->SetParent(nullptr);
	m_pChildren[idx]->SetChildIdx(-1);

	m_pChildren.erase(m_pChildren.begin() + idx);
}

void GameObject::ClearAllChildren()
{
	for (const auto& child : m_pChildren)
	{
		child->SetParent(nullptr);
		child->SetChildIdx(-1);
	}
	m_pChildren.clear();
}

void GameObject::SetParent(GameObject* pNewParent)
{
	if (pNewParent == this)
	{
		std::cerr << "\n-- WARNING--\nParent is not valid\n---------------\n";
		return;
	}

	if (pNewParent == nullptr)
	{
		m_pParent = pNewParent;
		return;
	}

	m_pParent = pNewParent;
	//pNewParent->AddChild(std::shared_ptr<GameObject>(this));
	m_IsTransformDirty = true;
}

#pragma endregion