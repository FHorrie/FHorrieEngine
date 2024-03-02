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

		void SetPosition(float x, float y);

		int AddComponent(Component* pComponent);
		int AddComponent(std::unique_ptr<Component> pComponent);
		bool CheckComponent(std::unique_ptr<Component> pComponent);
		bool CheckComponent(int idx);
		const Component* GetComponentWithIdx(int idx);
		void ClearComponentWithIdx(int idx);
		void ClearAllComponents();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform{};

		std::vector<std::unique_ptr<Component>> m_pComponents;
		int m_CurrentHash{};
	};
}

class ComponentIdxOutOfRangeException{};
class MaxComponentsReachedException{};