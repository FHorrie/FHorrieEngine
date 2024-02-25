#pragma once
#include "GameObject.h"

namespace dae
{
	class Component
	{
	public:
		virtual void Update() = 0;
		virtual void Render() const = 0;

		Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	};
}