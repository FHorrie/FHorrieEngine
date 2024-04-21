#include "Time.h"

void FH::Time::UpdateTime(const std::chrono::steady_clock::time_point& time)
{
	const std::chrono::duration<double, std::milli> deltaMillis{(time - PREVTIME)};
	PREVTIME = time;

	DELTATIME = deltaMillis.count() / 1000.0;

	ELAPSEDTIME += DELTATIME;
}