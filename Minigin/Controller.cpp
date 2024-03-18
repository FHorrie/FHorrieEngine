#include "Controller.h"
#include "GameObject.h"


using namespace dae;

void Controller::StoreInputMapping(std::unique_ptr<InputMapping>& inputMapping)
{
	if (m_pInputMap)
		m_pInputMap.reset();

	m_pInputMap = std::move(inputMapping);
}

void Controller::BindToControllerDevice(unsigned int controllerIdx)
{
	m_pController = std::make_unique<XController>(controllerIdx);
}

void Controller::ProcessControllerInput()
{
	if (!m_pController)
		return;

	m_pInputMap->HandleControllerInput(m_pController.get());
}

void Controller::ProcessKeyboardInput(SDL_Event& sdlEvent)
{
	m_pInputMap->HandleKeyboardInput(sdlEvent);
}