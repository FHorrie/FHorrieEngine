#pragma once
#include "Component.h"
#include "TextComponent.h"

namespace FH
{
	class FPSCounter final : public Component
	{
	public:
		FPSCounter(GameObject* pOwner);
		FPSCounter(GameObject* pOwner, int fontSize);
		virtual ~FPSCounter() = default;
		FPSCounter(const FPSCounter& other) = delete;
		FPSCounter(FPSCounter&& other) = delete;
		FPSCounter& operator=(const FPSCounter& other) = delete;
		FPSCounter& operator=(FPSCounter&& other) = delete;
		
		void Update() override;
		void Render() const override {};

	private:

		TextComponent* m_pTextComponent;
		int m_FrameCalls{};
		double m_AccuTime{};
		static constexpr double MAXTIME{0.5};
		static constexpr int FLOATINGPOINTACURRACY{ 1 };
	};
}

