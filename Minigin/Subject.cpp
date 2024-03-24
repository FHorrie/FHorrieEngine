#include "Observer.h"
#include "Subject.h"

using namespace FH;

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

void Subject::Notify(GameObject* go, GameEvent e)
{
	for (auto& obs : m_pObservers)
		obs->OnNotify(go, e);
}