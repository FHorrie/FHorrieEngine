#pragma once

namespace FH
{
	enum class Inputs
	{
		buttonSouth,
		buttonEast,
		buttonWest,
		buttonNorth,
		leftBumper,
		rightBumper,
		stickLeft,
		stickRight,
		dPadUp,
		dPadDown,
		dPadRight,
		dPadLeft,
		startButton,
		leftStickUp,
		leftStickDown,
		leftStickRight,
		leftStickLeft,
		rightStickUp,
		rightStickDown,
		rightStickRight,
		rightStickLeft,
	};

	enum class InputType
	{
		buttonPressed,
		buttonDown,
		buttonReleased,
		stick
	};

	class BaseInputDevice abstract
	{
	public:
		virtual void PollInput() = 0;
		virtual bool ValidateInput(Inputs input, InputType type) = 0;
	};
}
