#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>

#ifndef NDEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "DiggerApp.h"

int main(int, char* [])
{
	FH::DiggerApp app{};
	app.Run();
	return 0;
}