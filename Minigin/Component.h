#pragma once
#include <memory>
#include "GameObject.h"

namespace dae
{
	class Component
	{
	public:
		virtual void Update() {};
		virtual void Render() const {};
		virtual void RenderUI() {};
		
		void AttachToNewObject(GameObject* gameObject);
		int GetComponentIdx() const { return m_ComponentIdx; }

		Component(GameObject* pOwner);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = default;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = default;

	protected:
		GameObject* GetOwner() const { return m_pOwner; }
		Transform GetParentTransform() const;

	private:
		GameObject* m_pOwner;
		int m_ComponentIdx{};
	};
}