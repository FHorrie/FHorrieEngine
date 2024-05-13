#pragma once
#include "GameObject.h"
#include "TransformComponent.h"

namespace FH
{
	class Command abstract
	{
	public:
		Command(GameObject* pGameObject)
			: m_pGameObject{ pGameObject }
		{}
		virtual ~Command() = default;
		virtual void Execute() = 0;
	protected:
		GameObject* GetGameObjectPtr() { return m_pGameObject; }
	private:
		GameObject* m_pGameObject;
	};	
}


