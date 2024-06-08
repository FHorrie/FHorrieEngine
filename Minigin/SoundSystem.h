#pragma once
#include "SoundBase.h"

namespace FH
{
	class SoundSystem final : public SoundBase
	{
	public:
		SoundSystem();
		~SoundSystem();
		SoundSystem(const SoundSystem&) = delete;
		SoundSystem(SoundSystem&&) = default;
		SoundSystem& operator=(const SoundSystem&) = delete;
		SoundSystem& operator=(SoundSystem&&) = default;

		virtual void LoadSound(soundId newId, const std::string& path) override;
		virtual void LoadSong(soundId newId, const std::string& path) override;
		virtual void Play(soundId id, float volume) override;
		virtual void PlaySong(soundId id, float volume, bool loop) override;
		virtual void StopSong() override;
		virtual void PauseSong() override;
		virtual void ResumeSong() override;
		virtual void StopAll() override;

	private:
		class SoundSystemImpl;
		SoundSystemImpl* m_pImpl;

	};
}