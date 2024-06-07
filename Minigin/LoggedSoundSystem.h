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

		virtual void Play(soundId id, float volume) override;
		virtual void PlaySong(soundId id, float volume, bool loop) override;
		virtual void StopSong() override;
		virtual void PauseSong() override;
		virtual void ResumeSong() override;
		virtual void StopAll() override;

	private:
		void LogConsole(const std::string& message);
		SoundBase& m_WrappedSystem;
	};
}