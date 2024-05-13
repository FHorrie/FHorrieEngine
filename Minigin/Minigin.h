#pragma once
#include <string>
#include <functional>

#include "Renderer.h"

namespace FH
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		static constexpr int SCREENSIZEMULTIPLIER{ 3 };

		static constexpr int WINDOWWIDTH{ Renderer::GetLogicalWidth() * SCREENSIZEMULTIPLIER };
		static constexpr int WINDOWHEIGHT{ Renderer::GetLogicalHeight() * SCREENSIZEMULTIPLIER };
	};
}