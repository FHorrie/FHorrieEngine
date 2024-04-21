#include "InputMapping.h"

void FH::InputMapping::BindAction(std::unique_ptr<Action>& pAction, const ControllerInputVec& inputDesc, const std::vector<SDL_Scancode>& keyboardInput)
{
	m_InputMapVec.push_back(std::make_tuple(std::move(pAction), inputDesc, keyboardInput));
}

void FH::InputMapping::HandleControllerInput(XInputController* controller)
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

void FH::InputMapping::HandleKeyboardInput()
{
	//Make keyboard input fast as duck
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