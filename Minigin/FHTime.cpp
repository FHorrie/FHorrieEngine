#include "FHTime.h"

void FH::Time::UpdateTime(const std::chrono::steady_clock::time_point& time)
{
	const std::chrono::duration<float, std::milli> deltaMillis{(time - PREVTIME)};
	PREVTIME = time;

	DELTATIME = deltaMillis.count() / 1000.0f;

	ELAPSEDTIME += DELTATIME;
}