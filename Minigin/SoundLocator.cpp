#include "SoundLocator.h"

void FH::SoundLocator::RegisterSystem(std::unique_ptr<SoundBase> service)
{
	if (service.get() == nullptr)
		//Fall back to nullservice
		SERVICE = std::make_unique<NullSoundSystem>();
	else
		SERVICE = std::move(service);
}