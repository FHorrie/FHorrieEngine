#include "Component.h"
#include <iostream>

using namespace dae;

Component::Component(std::shared_ptr<GameObject> pOwner)
	: m_pOwner{ pOwner }
{
	try
	{
		m_ComponentIdx = pOwner->AddComponent(this);
	}
	catch (...)
	{
		std::cerr << "\n-- WARNING --\nGameObject cannot handle more components\n-------------\n";
		m_pOwner.reset();
	}
}

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