#pragma once
#include "Command.h"

namespace FH
{
	class Action final
	{
	public:
		Action(std::unique_ptr<Command> command)
			: m_pCommand{ std::move(command) }
		{}
		~Action() = default;
		Action(const Action& other) = delete;
		Action(Action&& other) = delete;
		Action& operator=(const Action& other) = delete;
		Action& operator=(Action&& other) = delete;

		inline Command* GetCommandPtr() { return m_pCommand.get(); }

	private:
		std::unique_ptr<Command> m_pCommand;

	};
}