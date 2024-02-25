#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class Component;

	// todo: this should become final.
	class GameObject final
	{
	public:
		void Update();
		void Render() const;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		int AddComponent(std::shared_ptr<Component> pComponent);
		bool CheckComponent(std::shared_ptr<Component> pComponent);
		std::shared_ptr<Component> GetComponentWithIdx(int idx);
		void ClearComponentWithIdx(int idx);
		void ClearAllComponents();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};

		std::vector<std::shared_ptr<Component>> m_pComponents;
		int m_ComponentAmount;
	};
}

class ComponentIdxOutOfRangeException{};
class MaxComponentsReachedException{};