#include "LoggedSoundSystem.h"
#include <format>
#include <iostream>

FH::LoggedSoundSystem::LoggedSoundSystem(SoundBase& wrappedSystem)
	: m_WrappedSystem{ wrappedSystem }
{}

void FH::LoggedSoundSystem::Play(soundId id, int volume)
{
	LogConsole(std::format("Playing single sound with id {} at {} volume", id, volume));
	m_WrappedSystem.Play(id, volume);
}

//void FH::LoggedSoundSystem::PlayLooped(soundId id, float volume)
//{
//	LogConsole(std::format("Playing looped sound with id {} at {} volume", id, volume));
//	m_WrappedSystem.PlayLooped(id, volume);
//}

void FH::LoggedSoundSystem::TryStop(soundId id)
{
	LogConsole(std::format("Tried to stop all sounds with id {}", id));
	m_WrappedSystem.TryStop(id);
}

void FH::LoggedSoundSystem::StopAll()
{
	LogConsole("Stopped ALL sounds");
	m_WrappedSystem.StopAll();
}

void FH::LoggedSoundSystem::LogConsole(const std::string& message)
{
	std::cout << message << std::endl;
}