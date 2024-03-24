#include "InputMapping.h"

using namespace FH;

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

void InputMapping::HandleKeyboardInput()
{
	const uint8_t* keyboardState{ SDL_GetKeyboardState(nullptr) };

	for (const auto& inputMap : m_InputMapVec)
	{
		for (const auto& keyboardInput : std::get<2>(inputMap))
		{
			if (keyboardState[keyboardInput])
			{
				std::get<0>(inputMap)->GetCommandPtr()->Execute();
				break;
			}
		}
	}
}