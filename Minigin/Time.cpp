#include "Time.h"

using namespace dae;

double Time::DELTATIME{0.01};
double Time::ELAPSEDTIME{0.01};
std::chrono::steady_clock::time_point Time::PREVTIME{ std::chrono::steady_clock::now() };

void Time::UpdateTime(const std::chrono::steady_clock::time_point& time)
{
	const std::chrono::duration<double, std::milli> deltaNano{(time - PREVTIME)};
	PREVTIME = time;

	DELTATIME = deltaNano.count() / 1000.0;

	ELAPSEDTIME += DELTATIME;
}