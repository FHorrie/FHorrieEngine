#include "SoundLocator.h"

void FH::SoundLocator::RegisterSystem(std::unique_ptr<SoundBase> service)
{
	if (service.get() == nullptr)
		//Fall back to nullservice
		SERVICE = std::make_unique<NullSoundSystem>();
	else
		SERVICE = std::move(service);
}

FH::SoundBase& FH::SoundLocator::GetSoundService()
{
	if (!MUTED)
		return *SERVICE.get();
	else
		return *MUTE_SERVICE.get();
}

void FH::SoundLocator::ToggleMute()
{
	MUTED = !MUTED;

	if (MUTED)
	{
		SERVICE->PauseSong();
		SERVICE->StopAll();
	}
	else
		SERVICE->ResumeSong();
}