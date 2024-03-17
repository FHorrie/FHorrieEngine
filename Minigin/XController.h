#pragma once
#include "BaseInputDevice.h"

namespace dae
{
	class XController final : public BaseInputDevice
	{
	public:
		XController(unsigned int playerIdx);
		~XController();
		XController(const XController& other) = delete;
		XController(XController&& other) = delete;
		XController& operator=(const XController& other) = delete;
		XController& operator=(XController&& other) = delete;

		void PollInput() override;
		bool ValidateInput(Inputs input, InputType inputType) override;

	private:
		class XControllerImpl;
		XControllerImpl* m_pImpl;
	};
}