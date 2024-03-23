#include "Observer.h"
#include "SubjectComponent.h"

using namespace FH;

///
/// Subject Component
///

SubjectComponent::SubjectComponent(GameObject* pOwner)
	: Component(pOwner)
{}

///
/// Subject
///

void Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void Subject::RemoveObserver(Observer* pObserver)
{
	auto componentIt = std::ranges::find(m_pObservers, pObserver);

	if (componentIt == m_pObservers.end())
		return;

	m_pObservers.erase(componentIt);
}

void Subject::Notify(Event e)
{
	for (auto& obs : m_pObservers)
		obs->OnNotify(this, e);
}