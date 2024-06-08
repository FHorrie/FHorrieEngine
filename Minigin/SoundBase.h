#pragma once
#include <string>

namespace FH
{
	using soundId = std::string;
	class SoundBase
	{
	public:
		virtual ~SoundBase() = default;
		virtual void LoadSound(soundId newId, const std::string& path) = 0;
		virtual void LoadSong(soundId newId, const std::string& path) = 0;
		virtual void Play(soundId id, float volume) = 0;
		virtual void PlaySong(soundId id, float volume, bool loop) = 0;
		virtual void StopSong() = 0;
		virtual void PauseSong() = 0;
		virtual void ResumeSong() = 0;
		virtual void StopAll() = 0;
	};

	class NullSoundSystem : public SoundBase
	{
	public:
		virtual void LoadSound(soundId newId, const std::string& path) { newId; path; }
		virtual void LoadSong(soundId newId, const std::string& path) { newId; path; }
		virtual void Play(soundId id, float volume) override { id; volume; }
		virtual void PlaySong(soundId id, float volume, bool loop) override { id; volume; loop; }
		virtual void StopSong() override {}
		virtual void PauseSong() override {}
		virtual void ResumeSong() override {}
		virtual void StopAll() override	{}
	};
}