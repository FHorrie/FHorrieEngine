#include "Component.h"
#include <iostream>

using namespace dae;

Component::Component(std::shared_ptr<GameObject> pOwner)
	: m_pOwner{ pOwner }
{}

void Component::AttachToNewObject(std::shared_ptr<GameObject> gameObject)
{
	if (gameObject == nullptr) 
	{
		std::cerr << "\n-- WARNING --\nPassed GameObject was nullptr\n-------------\n";
		return;
	}
	
	auto owner = m_pOwner.lock();
	
	if (owner != nullptr)
	{
		owner->ClearComponentWithIdx(m_ComponentIdx);
	}
	
	m_ComponentIdx = gameObject->AddComponent(this);
}

Transform Component::GetParentTransform() const 
{ 
	return m_pOwner.lock()->GetWorldTransform();
}