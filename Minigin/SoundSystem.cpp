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
	void PlaySound(soundId id, float volume = 128);

private:
	void PlaySoundQueue();

	static inline std::mutex m_SoundMutex{};
	std::unordered_map<soundId, Mix_Chunk*> m_SoundBible{};
	std::list<std::pair<soundId, float /*volume*/>> m_SoundEventQueue{};

	std::mutex m_PlayMutex{};
	std::jthread m_SoundThread{};
	bool m_CleanUpThread{};
};

FH::SoundSystem::SoundSystemImpl::SoundSystemImpl()
{
	LoadSound("Teleport", "../Data/Sounds/PlayerTeleported.ogg");
	//LoadSound("HFB", "../Data/Sounds/HundredFortyBillion.mp3");
	//LoadSound("Ligma", "../Data/Sounds/SteveJobs.mp3");

	m_SoundThread = std::jthread(&SoundSystemImpl::PlaySoundQueue, this);
}

FH::SoundSystem::SoundSystemImpl::~SoundSystemImpl()
{
	for (auto& sound : m_SoundBible)
	{
		Mix_FreeChunk(sound.second);
		sound.second = nullptr;
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
		const std::string errorMsg = "Sound failed to load " + path + "\n";
		std::cerr << errorMsg;
		return;
	}

	m_SoundBible.insert(std::pair(newId, chunk));
}

void FH::SoundSystem::SoundSystemImpl::PlaySound(soundId id, float volume)
{
	auto sound{ m_SoundBible.find(id) };

	if (sound == m_SoundBible.cend())
		return;

	m_SoundEventQueue.push_back({id, volume});
}

void FH::SoundSystem::SoundSystemImpl::PlaySoundQueue()
{
	do
	{
		if (m_SoundEventQueue.size() == 0)
			std::this_thread::yield();
		else
		{
			std::lock_guard<std::mutex> lock{m_PlayMutex};
			auto soundInfo{ m_SoundEventQueue.front() };
			m_SoundEventQueue.pop_front();

			const int mixVolume{ static_cast<int>(soundInfo.second * MIX_MAX_VOLUME) };

			const auto sound{ m_SoundBible.find(soundInfo.first) };

			Mix_VolumeChunk(sound->second, mixVolume);
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

void FH::SoundSystem::Play(soundId id, float volume)
{
	m_pImpl->PlaySound(id, volume);
}

void FH::SoundSystem::TryStop(soundId id)
{
	//Stops all sounds too
	//TODO: Figure out how to isolate the requested sound (channel indexes)
	id;
	Mix_HaltChannel(-1);
}

void FH::SoundSystem::StopAll()
{
	Mix_HaltChannel(-1);
}
