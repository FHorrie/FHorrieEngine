#include <Windows.h>
#include <SDL.h>
#include <Xinput.h>

#include "InputManager.h"
#include "SceneManager.h"
#include "SoundLocator.h"

bool FH::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYUP) {
			if (e.key.keysym.sym == SDLK_F1)
			{
				SoundLocator::GetSoundService().PlaySong("MainBGM", 0.4f, true);
				SceneManager::GetInstance().GoToNextScene();
			}
			if (e.key.keysym.sym == SDLK_F2)
				SoundLocator::ToggleMute();
			if (e.key.keysym.sym == SDLK_F3)
			{
				SoundLocator::GetSoundService().PlaySong("MainBGM", 0.4f, true);
				SceneManager::GetInstance().GoToStartScene();
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		//GUI
		//ImGui_ImplSDL2_ProcessEvent(&e);
	}

	int sceneIdx{ SceneManager::GetInstance().GetCurrentSceneIdx() };

	m_Controllers[sceneIdx]->ProcessKeyboardInput();
	m_Controllers[sceneIdx]->ProcessControllerInput();

	return true;
}

void FH::InputManager::AddController(std::unique_ptr<Controller>& controller)
{
	m_Controllers.push_back(std::move(controller));
}
