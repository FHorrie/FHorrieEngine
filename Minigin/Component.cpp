#include "Component.h"
#include <iostream>

using namespace dae;

Component::Component(GameObject* pOwner)
	: m_pOwner{ pOwner }
{}

void Component::AttachToNewObject(GameObject* gameObject)
{
	if (gameObject == nullptr) 
	{
		std::cerr << "\n-- WARNING --\nPassed GameObject was nullptr\n-------------\n";
		return;
	}
	
	if (m_pOwner != nullptr)
	{
		m_pOwner->ClearComponentWithIdx(m_ComponentIdx);
	}
	
	m_ComponentIdx = gameObject->AddComponent(this);
}

Transform Component::GetParentTransform() const 
{ 
	return m_pOwner->GetWorldTransform();
}