#include "LoggedSoundSystem.h"
#include <format>
#include <iostream>

FH::LoggedSoundSystem::LoggedSoundSystem(SoundBase& wrappedSystem)
	: m_WrappedSystem{ wrappedSystem }
{}

void FH::LoggedSoundSystem::Play(soundId id, float volume)
{
	LogConsole(std::format("Playing single sound with id {} at {} volume", id, volume));
	m_WrappedSystem.Play(id, volume);
}

void FH::LoggedSoundSystem::PlaySong(soundId id, float volume, bool loop)
{
	LogConsole(std::format("Playing song with id {} at {} volume", id, volume));
	m_WrappedSystem.PlaySong(id, volume, loop);
}

void FH::LoggedSoundSystem::StopSong()
{
	LogConsole("Stopped current song!");
	m_WrappedSystem.StopSong();
}

void FH::LoggedSoundSystem::PauseSong()
{
	LogConsole("Paused current song!");
	m_WrappedSystem.PauseSong();
}

void FH::LoggedSoundSystem::ResumeSong()
{
	LogConsole("Stopped current song!");
	m_WrappedSystem.ResumeSong();
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