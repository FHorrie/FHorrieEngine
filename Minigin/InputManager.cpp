#include <Windows.h>
#include <SDL.h>
#include <Xinput.h>

#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"

bool FH::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		//GUI
		//ImGui_ImplSDL2_ProcessEvent(&e);
	}

	for (auto& controller : m_Controllers)
		controller->ProcessKeyboardInput();

	for (auto& controller : m_Controllers)
		controller->ProcessControllerInput();

	return true;
}

void FH::InputManager::AddController(std::unique_ptr<Controller>& controller)
{
	m_Controllers.push_back(std::move(controller));
}
