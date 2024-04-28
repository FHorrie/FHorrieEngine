#pragma once
#include "SoundBase.h"

#include <string>

namespace FH
{
	class LoggedSoundSystem : public SoundBase
	{
	public:
		LoggedSoundSystem(SoundBase& wrappedSystem);
		~LoggedSoundSystem() = default;

		virtual void Play(soundId id, int volume = 128) override;
		//virtual void PlayLooped(soundId id, float volume) override;
		virtual void TryStop(soundId id) override;
		virtual void StopAll() override;

	private:
		void LogConsole(const std::string& message);
		SoundBase& m_WrappedSystem;
	};
}