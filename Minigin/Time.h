#pragma once
#include <chrono>

namespace FH
{
	class Time final
	{
	public:
		static double GetDeltaTime() { return DELTATIME; }
		static double GetElapsedTime() { return ELAPSEDTIME; }

		static void UpdateTime(const std::chrono::steady_clock::time_point& time);

		Time() = default;
		~Time() = default;
		Time(const Time& other) = delete;
		Time(Time&& other) = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) = delete;

	private:
		inline static double DELTATIME{ 0.01 };
		inline static double ELAPSEDTIME{ 0.01 };

		inline static std::chrono::steady_clock::time_point 
			PREVTIME{ std::chrono::steady_clock::now() };
	};
}