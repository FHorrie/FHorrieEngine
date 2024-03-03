#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class Component;
	class GameObject final
	{
	public:
		void Update();
		void Render() const;

		void SetLocalPosition(glm::vec3 pos);
		void UpdateTransform();
		Transform GetTransform() const { return m_Transform; }
		Transform GetWorldTransform();

		int AddComponent(Component* pComponent);
		int AddComponent(std::unique_ptr<Component> pComponent);

		bool CheckComponent(std::unique_ptr<Component> pComponent);
		bool CheckComponent(int idx);
		Component* GetComponentWithIdx(int idx);

		void ClearComponentWithIdx(int idx);
		void ClearAllComponents();


		GameObject* GetParent() const { return m_pParent; }
		int GetChildIdx() const { return m_ChildIdx; }

		void SetTransformDirty() { m_IsTransformDirty = true; }

		void AddChild(std::shared_ptr<GameObject> pObject);
		bool CheckChild(std::shared_ptr<GameObject> pObject);
		bool CheckChild(int idx);
		GameObject* GetChildWithIdx(int idx);
		void ClearChild(std::shared_ptr<GameObject> pObject);
		void ClearChildWithIdx(int idx);
		void ClearAllChildren();


		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void SetParent(GameObject* pNewParent);
		void SetChildIdx(int newIdx) { m_ChildIdx = newIdx; }
		
		Transform m_Transform{};
		Transform m_ParentTransform{};
		bool m_IsTransformDirty{};

		Transform m_WorldTransform{};

		GameObject* m_pParent{};
		int m_ChildIdx{ -1 }; //init with -1 because we have no parent object

		std::vector<std::shared_ptr<GameObject>> m_pChildren{};

		std::vector<std::unique_ptr<Component>> m_pComponents;
	};
}

class ComponentOutOfRangeException{};
class MaxComponentsReachedException{};
class ChildOutOfRangeException{};
class MaxChildrenReachedException{};