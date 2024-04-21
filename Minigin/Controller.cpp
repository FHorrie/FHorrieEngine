#include "Controller.h"
#include "GameObject.h"

void FH::Controller::StoreInputMapping(std::unique_ptr<InputMapping>& inputMapping)
{
	if (m_pInputMap)
		m_pInputMap.reset();

	m_pInputMap = std::move(inputMapping);
}

void FH::Controller::BindToControllerDevice(unsigned int controllerIdx)
{
	m_pController = std::make_unique<XInputController>(controllerIdx);
}

void FH::Controller::ProcessControllerInput()
{
	if (!m_pController)
		return;

	m_pInputMap->HandleControllerInput(m_pController.get());
}

void FH::Controller::ProcessKeyboardInput()
{
	m_pInputMap->HandleKeyboardInput();
}