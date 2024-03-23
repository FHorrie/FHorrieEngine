#include "Time.h"

using namespace FH;

double Time::DELTATIME{0.01};
double Time::ELAPSEDTIME{0.01};
std::chrono::steady_clock::time_point Time::PREVTIME{ std::chrono::steady_clock::now() };

void Time::UpdateTime(const std::chrono::steady_clock::time_point& time)
{
	const std::chrono::duration<double, std::milli> deltaMillis{(time - PREVTIME)};
	PREVTIME = time;

	DELTATIME = deltaMillis.count() / 1000.0;

	ELAPSEDTIME += DELTATIME;
}