#pragma once
#include <SDL.h>
#include <vector>
#include <map>
#include "Action.h"
#include "XController.h"

namespace FH
{
	class InputMapping final
	{
	public:
		using inputTypeDesc = std::vector<std::pair<Inputs, InputType>>;

		InputMapping() = default;
		~InputMapping() = default;
		InputMapping(const InputMapping& other) = delete;
		InputMapping(InputMapping&& other) = delete;
		InputMapping& operator=(const InputMapping& other) = delete;
		InputMapping& operator=(InputMapping&& other) = delete;

		void BindAction(std::unique_ptr<Action>& pAction, const inputTypeDesc& inputDesc, const std::vector<SDL_Scancode>& keyboardInput);

		void HandleControllerInput(XController* controller);
		void HandleKeyboardInput();

	private:
		//Not optimal, but works for both keyboard and controller
		std::vector<std::tuple<std::unique_ptr<Action>,inputTypeDesc, std::vector<SDL_Scancode>>> m_InputMapVec{};
	};
}