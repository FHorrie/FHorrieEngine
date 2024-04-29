#pragma once
#include <string>

namespace FH
{
	using soundId = std::string;
	class SoundBase
	{
	public:
		virtual ~SoundBase() = default;
		virtual void Play(soundId id, float volume) = 0;
		//virtual void PlayLooped(soundId id, float volume) = 0;
		virtual void TryStop(soundId id) = 0;
		virtual void StopAll() = 0;
	};

	class NullSoundSystem : public SoundBase
	{
	public:
		virtual void Play(soundId id, float volume) override { id; volume; }
		//virtual void PlayLooped(soundId id, float volume) override {}
		virtual void TryStop(soundId id) override { id; }
		virtual void StopAll() override	{}
	};
}