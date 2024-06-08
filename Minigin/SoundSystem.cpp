#include "SoundSystem.h"

#include <SDL_mixer.h>
#include <unordered_map>
#include <string>
#include <format>
#include <iostream>
#include <mutex>
#include <future>

class FH::SoundSystem::SoundSystemImpl
{
public:
	SoundSystemImpl();
	~SoundSystemImpl();
	SoundSystemImpl(const SoundSystemImpl&) = delete;
	SoundSystemImpl(SoundSystemImpl&&) = default;
	SoundSystemImpl& operator=(const SoundSystemImpl&) = delete;
	SoundSystemImpl& operator=(SoundSystemImpl&&) = default;

	void LoadSound(soundId newId, const std::string& path);
	void LoadSong(soundId newId, const std::string& path);

	void PlaySound(soundId id, float volume);
	void PlaySong(soundId id, float volume, bool loop);
	void PauseSong() const { Mix_PauseMusic(); }
	void ResumeSong() const { Mix_ResumeMusic(); }
	void StopSong() const { Mix_HaltMusic(); }

private:
	void PlaySoundQueue();

	static inline std::mutex m_SoundMutex{};
	std::unordered_map<soundId, Mix_Chunk*> m_SoundBible{};
	std::unordered_map<soundId, Mix_Music*> m_MusicBible{};
	std::list<std::pair<soundId, int /*volume*/>> m_SoundEventQueue{};

	std::mutex m_PlayMutex{};
	std::jthread m_SoundThread{};
	bool m_CleanUpThread{};
};

FH::SoundSystem::SoundSystemImpl::SoundSystemImpl()
{
	m_SoundThread = std::jthread(&SoundSystemImpl::PlaySoundQueue, this);
}

FH::SoundSystem::SoundSystemImpl::~SoundSystemImpl()
{
	for (auto& sound : m_SoundBible)
	{
		Mix_FreeChunk(sound.second);
		sound.second = nullptr;
	}

	for (auto& song : m_MusicBible)
	{
		Mix_FreeMusic(song.second);
		song.second = nullptr;
	}

	m_CleanUpThread = true;
}

void FH::SoundSystem::SoundSystemImpl::LoadSound(soundId newId, const std::string& path)
{
	if (m_SoundBible.contains(newId))
	{
		std::cerr << "Error!: sound id is already in use, sound " + path + " was not loaded\n";
		return;
	}

	auto chunk{ Mix_LoadWAV(path.c_str()) };

	if (chunk == nullptr)
	{
		std::cerr << "Sound failed to load " + path + "\n";
		return;
	}

	m_SoundBible.insert({ newId, chunk });
}

void FH::SoundSystem::SoundSystemImpl::LoadSong(soundId newId, const std::string& path)
{
	if (m_MusicBible.contains(newId))
	{
		std::cerr << "Error!: sound id is already in use, " + path + " was not loaded\n";
		return;
	}

	auto chunk{ Mix_LoadMUS(path.c_str()) };

	if (chunk == nullptr)
	{
		std::cerr << "Song failed to load: " + path + "\n";
		return;
	}

	m_MusicBible.insert({ newId, chunk });
}

void FH::SoundSystem::SoundSystemImpl::PlaySound(soundId id, float volume)
{
	auto sound{ m_SoundBible.find(id) };

	if (sound == m_SoundBible.cend())
		return;

	m_SoundEventQueue.push_back({id, int(volume * 128)});
}

void FH::SoundSystem::SoundSystemImpl::PlaySong(soundId id, float volume, bool loop)
{
	auto song{ m_MusicBible.find(id) };

	if (song == m_MusicBible.cend())
		return;
	Mix_VolumeMusic(int(volume * 128));
	Mix_PlayMusic(song->second, loop ? -1 : 1);
}

void FH::SoundSystem::SoundSystemImpl::PlaySoundQueue()
{
	do
	{
		if (m_SoundEventQueue.size() == 0)
			std::this_thread::yield();
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			auto soundInfo{ m_SoundEventQueue.front() };
			m_SoundEventQueue.pop_front();
			const auto sound{ m_SoundBible.find(soundInfo.first) };

			Mix_VolumeChunk(sound->second, soundInfo.second);
			Mix_PlayChannel(-1, sound->second, 0);
		}
	} while (!m_CleanUpThread);
}

//pImpl end

FH::SoundSystem::SoundSystem()
	: m_pImpl{ new SoundSystemImpl() }
{}

FH::SoundSystem::~SoundSystem()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}

void FH::SoundSystem::LoadSound(soundId newId, const std::string& path)
{
	m_pImpl->LoadSound(newId, path);
}

void FH::SoundSystem::LoadSong(soundId newId, const std::string& path)
{
	m_pImpl->LoadSong(newId, path);
}

void FH::SoundSystem::Play(soundId id, float volume)
{
	m_pImpl->PlaySound(id, volume);
}

void FH::SoundSystem::PlaySong(soundId id, float volume, bool loop)
{
	m_pImpl->PlaySong(id, volume, loop);
}

void FH::SoundSystem::StopSong()
{
	m_pImpl->StopSong();
}

void FH::SoundSystem::PauseSong()
{
	m_pImpl->PauseSong();
}

void FH::SoundSystem::ResumeSong()
{
	m_pImpl->ResumeSong();
}

void FH::SoundSystem::StopAll()
{
	Mix_HaltChannel(-1);
}
