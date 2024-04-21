#pragma once
#include "BaseInputDevice.h"

namespace FH
{
	class XInputController final : public BaseInputDevice
	{
	public:
		XInputController(unsigned int playerIdx);
		~XInputController();
		XInputController(const XInputController&) = delete;
		XInputController(XInputController&&) = default;
		XInputController& operator=(const XInputController&) = delete;
		XInputController& operator=(XInputController&&) = default;

		void PollInput() override;
		bool ValidateInput(Inputs input, InputType inputType) override;

	private:
		class XInputControllerImpl;
		XInputControllerImpl* m_pImpl;
	};
}