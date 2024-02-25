#pragma once
#include <chrono>

namespace dae
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
		static double DELTATIME;
		static double ELAPSEDTIME;

		static std::chrono::steady_clock::time_point PREVTIME;
	};
}