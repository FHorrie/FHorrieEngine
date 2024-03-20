#include "InputMapping.h"

using namespace dae;

void InputMapping::BindAction(std::unique_ptr<Action>& pAction, SDL_Scancode input)
{
	BindAction(pAction, inputTypeDesc{}, std::vector<SDL_Scancode>(input));
}

void InputMapping::BindAction(std::unique_ptr<Action>& pAction, const std::vector<SDL_Scancode>& input)
{
	BindAction(pAction, inputTypeDesc{}, input);
}

void InputMapping::BindAction(std::unique_ptr<Action>& pAction, const inputTypeDesc& inputDesc)
{
	BindAction(pAction, inputDesc, std::vector<SDL_Scancode>());
}

void InputMapping::BindAction(std::unique_ptr<Action>& pAction, const inputTypeDesc& inputDesc, const std::vector<SDL_Scancode>& keyboardInput)
{
	m_InputMapVec.push_back(std::make_tuple(std::move(pAction), inputDesc, keyboardInput));
}

void InputMapping::HandleControllerInput(XController* controller)
{
	controller->PollInput();

	for (const auto& inputMap : m_InputMapVec)
	{
		for (const auto& controllerInput : std::get<1>(inputMap))
		{
			if (controller->ValidateInput(controllerInput.first, controllerInput.second))
			{
				std::get<0>(inputMap)->GetCommandPtr()->Execute();
				break;
			}
		}
	}
}

void InputMapping::HandleKeyboardInput(SDL_Event& sdlEvent)
{
	for (const auto& inputMap : m_InputMapVec)
	{
		for (const auto& keyboardInput : std::get<2>(inputMap))
		{
			if (keyboardInput == sdlEvent.key.keysym.scancode)
			{
				std::get<0>(inputMap)->GetCommandPtr()->Execute();
				break;
			}
		}
	}
}