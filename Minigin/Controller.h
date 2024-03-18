#pragma once
#include <memory>
#include <SDL.h>

#include "XController.h"
#include "InputMapping.h"

namespace dae
{
	class GameObject;
	class Controller final
	{
	public:
		Controller() = default;
		~Controller() = default;
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void StoreInputMapping(std::unique_ptr<InputMapping>& inputMapping);
		void BindToControllerDevice(unsigned int controllerIdx);
		void ProcessControllerInput();
		void ProcessKeyboardInput(SDL_Event& sdlEvent);
	private:
		std::unique_ptr<InputMapping> m_pInputMap{};
		std::unique_ptr<XController> m_pController{};
	};
}