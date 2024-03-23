#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace FH
{
	class FPSCounter final : public Component
	{
	public:
		void Update() override;
		void Render() const override {};

		FPSCounter(GameObject* pOwner);
		virtual ~FPSCounter() = default;
		FPSCounter(const FPSCounter& other) = delete;
		FPSCounter(FPSCounter&& other) = delete;
		FPSCounter& operator=(const FPSCounter& other) = delete;
		FPSCounter& operator=(FPSCounter&& other) = delete;
	private:

		TextComponent* m_pTextComponent;
		int m_FrameCalls{};
		double m_AccuTime{};
		static constexpr double MAXTIME{0.5};
		static constexpr int FLOATINGPOINTACURRACY{ 1 };
	};
}

