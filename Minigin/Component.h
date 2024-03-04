#pragma once
#include <memory>
#include "GameObject.h"

namespace dae
{
	class Component
	{
	public:
		virtual void Update() = 0;
		virtual void Render() const = 0;
		
		void AttachToNewObject(std::shared_ptr<GameObject>);
		int GetComponentIdx() const { return m_ComponentIdx; }

		Component(std::shared_ptr<GameObject> pOwner);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = default;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = default;

	protected:
		std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
		Transform GetParentTransform() const;

	private:
		std::weak_ptr<GameObject> m_pOwner;
		int m_ComponentIdx{};
	};
}