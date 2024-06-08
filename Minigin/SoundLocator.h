#pragma once
#include "SoundBase.h"
#include <memory>

namespace FH
{
	class SoundLocator final
	{
	public:
		static void RegisterSystem(std::unique_ptr<SoundBase> service);

		static SoundBase& GetSoundService();

		static void ToggleMute();

	private:
		inline static bool MUTED{};

		inline static std::unique_ptr<SoundBase> SERVICE 
			= std::make_unique<NullSoundSystem>();
		inline static std::unique_ptr<SoundBase> MUTE_SERVICE
			= std::make_unique<NullSoundSystem>();
	};
}
