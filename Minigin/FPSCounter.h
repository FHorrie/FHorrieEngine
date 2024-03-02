#pragma once
#include "Component.h"
#include "TextComponent.h"
#include <array>

namespace dae
{
	class FPSCounter final : public Component
	{
	public:
		void Update() override;
		void Render() const override {};

		FPSCounter(std::shared_ptr<GameObject> pOwner);
		virtual ~FPSCounter() = default;
		FPSCounter(const FPSCounter& other) = delete;
		FPSCounter(FPSCounter&& other) = delete;
		FPSCounter& operator=(const FPSCounter& other) = delete;
		FPSCounter& operator=(FPSCounter&& other) = delete;
	private:
		//static constexpr int FPSBUFFER{ 240 };

		std::shared_ptr<TextComponent> m_pTextComponent;
		int m_FrameCalls{};
		double m_AccuTime{};
		static constexpr double MAXTIME{0.5};
		static constexpr int FLOATINGPOINTACURRACY{ 1 };
		//std::array<float, FPSBUFFER> m_FPSStored{};
	};
}

