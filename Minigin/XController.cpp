#include <windows.h>
#pragma comment(lib, "Xinput.lib")
#include <Xinput.h>
#include "XController.h"
#include <glm/exponential.hpp>

class FH::XInputController::XInputControllerImpl
{
public:
	XInputControllerImpl(int playerIdx);
	~XInputControllerImpl() = default;
	XInputControllerImpl(const XInputControllerImpl&) = delete;
	XInputControllerImpl(XInputControllerImpl&&) = default;
	XInputControllerImpl& operator=(const XInputControllerImpl&) = delete;
	XInputControllerImpl& operator=(XInputControllerImpl&&) = default;

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

	float m_NormalizedLX{};
	float m_NormalizedLY{};
	float m_NormalizedRX{};
	float m_NormalizedRY{};

	int m_PlayerIdx;
};

FH::XInputController::XInputControllerImpl::XInputControllerImpl(int playerIdx)
	: m_PlayerIdx{ playerIdx }
{}

void FH::XInputController::XInputControllerImpl::CheckForInput()
{
	CopyMemory(&m_PrevState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_PlayerIdx, &m_CurrentState);

	float LX = m_CurrentState.Gamepad.sThumbLX;
	float LY = m_CurrentState.Gamepad.sThumbLX;

	float RX = m_CurrentState.Gamepad.sThumbRX;
	float RY = m_CurrentState.Gamepad.sThumbRY;

	float magnitudeL = glm::sqrt(LX*LX + LY+LY);
	float magnitudeR = glm::sqrt(RX*RX + RY+RY);

	m_NormalizedLX = LX / magnitudeL;
	m_NormalizedLY = LY / magnitudeL;
	m_NormalizedRX = RX / magnitudeR;
	m_NormalizedRY = RY / magnitudeR;

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PrevState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges& m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges& (~m_CurrentState.Gamepad.wButtons);
}

bool FH::XInputController::XInputControllerImpl::ButtonDownThisFrame(unsigned int inputInt) const
{
	return m_ButtonsPressedThisFrame & inputInt;
}

bool FH::XInputController::XInputControllerImpl::ButtonUpThisFrame(unsigned int inputInt) const
{
	return m_ButtonsReleasedThisFrame & inputInt;
}

bool FH::XInputController::XInputControllerImpl::ButtonPressed(unsigned int inputInt) const
{
	return m_CurrentState.Gamepad.wButtons & inputInt;
}

int FH::XInputController::XInputControllerImpl::GetXInput(Inputs input)
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
	case Inputs::startButton:
		return XINPUT_GAMEPAD_START;
	default:
		return -1;
	}
}

FH::XInputController::XInputController(unsigned int playerIdx)
	: m_pImpl{ new XInputControllerImpl(playerIdx) }
{}

FH::XInputController::~XInputController()
{ 
	delete m_pImpl;
	m_pImpl = nullptr; 
}

void FH::XInputController::PollInput()
{
	m_pImpl->CheckForInput();
}

bool FH::XInputController::ValidateInput(Inputs input, InputType inputType)
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