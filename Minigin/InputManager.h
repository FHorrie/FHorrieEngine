#pragma once
#include <vector>
#include "Singleton.h"
#include "Controller.h"
#include "XController.h"

namespace FH
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddController(std::unique_ptr<Controller>& controller);
	private:
		std::vector<std::unique_ptr<Controller>> m_Controllers{};
		XController m_Controller{ 0 };
	};

}
