#pragma once
#include "SoundBase.h"
#include <memory>

namespace FH
{
	class SoundLocator final
	{
	public:
		static void RegisterSystem(std::unique_ptr<SoundBase> service);

		static SoundBase& GetSoundService() { return *SERVICE.get(); }

	private:
		inline static std::unique_ptr<SoundBase> SERVICE 
			= std::make_unique<NullSoundSystem>();
	};
}
