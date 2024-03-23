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
		dPadDown,
		dPadRight,
		dPadLeft,
		dPadUp
		//leftTrigger,
		//rightTrigger,
	};

	enum class InputType
	{
		buttonPressed,
		buttonDown,
		buttonReleased
	};

	class BaseInputDevice abstract
	{
	public:
		virtual void PollInput() = 0;
		virtual bool ValidateInput(Inputs input, InputType type) = 0;
	};
}
