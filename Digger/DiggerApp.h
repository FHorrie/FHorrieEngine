#pragma once
#include "Scene.h"

namespace FH
{
	class DiggerApp final
	{
	public:
		DiggerApp() = default;
		~DiggerApp() = default;
		DiggerApp(const DiggerApp&) = delete;
		DiggerApp(DiggerApp&&) = default;
		DiggerApp& operator=(const DiggerApp&) = delete;
		DiggerApp& operator=(DiggerApp&&) = default;

		void Run();

	private:
		void LoadAll();

		void LoadBackground(Scene& scene);
		void AddPlayerInput(Scene& scene);
	};
}


