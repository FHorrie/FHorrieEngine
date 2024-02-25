#pragma once
#include "TextComponent.h"
#include <array>

namespace dae
{
	class FPSCounter final : public TextComponent
	{
	public:
		void Update() override;

		FPSCounter(std::shared_ptr<Font> font, float left, float top);
		virtual ~FPSCounter() = default;
		FPSCounter(const FPSCounter& other) = delete;
		FPSCounter(FPSCounter&& other) = delete;
		FPSCounter& operator=(const FPSCounter& other) = delete;
		FPSCounter& operator=(FPSCounter&& other) = delete;
	private:
		static constexpr int FPSBUFFER{ 60 };
		static constexpr int FLOATINGPOINTACURRACY{ 1 };
		int m_FPSCount{};
		std::array<float, FPSBUFFER> m_FPSStored{};
	};
}

