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

		virtual void Play(soundId id, float volume = 128) override;
		//virtual void PlayLooped(soundId id, float volume) override;
		virtual void TryStop(soundId id) override;
		virtual void StopAll() override;

	private:
		class SoundSystemImpl;
		SoundSystemImpl* m_pImpl;

	};
}