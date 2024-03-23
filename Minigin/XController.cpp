#include <windows.h>
#pragma comment(lib, "Xinput.lib")
#include <Xinput.h>
#include "XController.h"

using namespace FH;

class XController::XControllerImpl
{
public:
	XControllerImpl(unsigned int playerIdx);
	~XControllerImpl() = default;
	XControllerImpl(const XControllerImpl& other) = delete;
	XControllerImpl(XControllerImpl&& other) = delete;
	XControllerImpl& operator=(const XControllerImpl& other) = delete;
	XControllerImpl& operator=(XControllerImpl&& other) = delete;

	void CheckForInput();

	//This will go into ValidateInput
	bool ButtonDownThisFrame(unsigned int input) const;
	bool ButtonUpThisFrame(unsigned int input) const;
	bool ButtonPressed(unsigned int input) const;
	int GetXInput(Inputs input);

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PrevState{};

	unsigned int m_ButtonsPressedThisFrame{};
	unsigned int m_ButtonsReleasedThisFrame{};
	unsigned int m_PlayerIdx;
};

XController::XControllerImpl::XControllerImpl(unsigned int playerIdx)
	: m_PlayerIdx{ playerIdx }
{}

void XController::XControllerImpl::CheckForInput()
{
	CopyMemory(&m_PrevState, & m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_PlayerIdx, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PrevState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges& m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges& (~m_CurrentState.Gamepad.wButtons);
}

bool XController::XControllerImpl::ButtonDownThisFrame(unsigned int inputInt) const
{
	return m_ButtonsPressedThisFrame & inputInt;
}

bool XController::XControllerImpl::ButtonUpThisFrame(unsigned int inputInt) const
{
	return m_ButtonsReleasedThisFrame & inputInt;
}

bool XController::XControllerImpl::ButtonPressed(unsigned int inputInt) const
{
	return m_CurrentState.Gamepad.wButtons & inputInt;
}

int XController::XControllerImpl::GetXInput(Inputs input)
{
	switch (input)
	{
	case Inputs::buttonSouth:
		return XINPUT_GAMEPAD_A;
	case Inputs::buttonEast:
		return XINPUT_GAMEPAD_B;
	case Inputs::buttonWest:
		return XINPUT_GAMEPAD_X;
	case Inputs::buttonNorth:
		return XINPUT_GAMEPAD_Y;
	case Inputs::dPadUp:
		return XINPUT_GAMEPAD_DPAD_UP;
	case Inputs::dPadDown:
		return XINPUT_GAMEPAD_DPAD_DOWN;
	case Inputs::dPadLeft:
		return XINPUT_GAMEPAD_DPAD_LEFT;
	case Inputs::dPadRight:
		return XINPUT_GAMEPAD_DPAD_RIGHT;
	case Inputs::stickLeft:
		return XINPUT_GAMEPAD_LEFT_THUMB;
	case Inputs::stickRight:
		return XINPUT_GAMEPAD_RIGHT_THUMB;
	case Inputs::leftBumper:
		return XINPUT_GAMEPAD_LEFT_SHOULDER;
	case Inputs::rightBumper:
		return XINPUT_GAMEPAD_RIGHT_SHOULDER;
	default:
		return -1;
	}
}

///
///Pimpl end
///

XController::XController(unsigned int playerIdx)
	: m_pImpl{ new XControllerImpl(playerIdx) }
{}

XController::~XController() 
{ 
	delete m_pImpl;
	m_pImpl = nullptr; 
}

void XController::PollInput()
{
	m_pImpl->CheckForInput();
}

bool XController::ValidateInput(Inputs input, InputType inputType)
{
	switch (inputType)
	{
	case InputType::buttonPressed:
		return m_pImpl->ButtonPressed(m_pImpl->GetXInput(input));
	case InputType::buttonDown:
		return m_pImpl->ButtonDownThisFrame(m_pImpl->GetXInput(input));
	case InputType::buttonReleased:
		return m_pImpl->ButtonUpThisFrame(m_pImpl->GetXInput(input));
	default:
		return false;
	}
}