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
		
		Component(std::shared_ptr<GameObject> pOwner);
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = default;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = default;

		void AttachToNewObject(std::shared_ptr<GameObject>);

		int GetComponentIdx() const { return m_ComponentIdx; }
	protected:

		//std::weak_ptr<GameObject> GetOwner() const { return m_pOwner; }
		std::weak_ptr<GameObject> m_pOwner;
		int m_ComponentIdx{};

	private:
	};
}