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
	static inline std::mutex m_SoundMutex{};
	std::unordered_map<soundId, Mix_Chunk*> m_SoundBible{};
};

FH::SoundSystem::SoundSystemImpl::SoundSystemImpl()
{
	LoadSound("Teleport", "../Data/Sounds/PlayerTeleported.ogg");
	//LoadSound("HFB", "../Data/Sounds/HundredFortyBillion.mp3");
	//LoadSound("Ligma", "../Data/Sounds/SteveJobs.mp3");
}

FH::SoundSystem::SoundSystemImpl::~SoundSystemImpl()
{
	for (auto& sound : m_SoundBible)
	{
		Mix_FreeChunk(sound.second);
		sound.second = nullptr;
	}
}

void FH::SoundSystem::SoundSystemImpl::LoadSound(soundId newId, const std::string& path)
{
	if (m_SoundBible.contains(newId))
	{
		std::cerr << "Error!: sound id is already in use, sound " + path + " was not loaded\n";
		return;
	}

	auto soundFuture{ std::async(std::launch::async, Mix_LoadWAV, path.c_str()) };

	if (soundFuture.valid())
	{
		const std::string errorMsg = "Sound failed to load " + path + "\n";
		std::cerr << errorMsg;
		return;
	}

	m_SoundBible.insert(std::pair(newId, soundFuture.get()));
}

void FH::SoundSystem::SoundSystemImpl::PlaySound(soundId id, float volume)
{
	auto sound{ m_SoundBible.find(id) };

	if (sound == m_SoundBible.cend())
		return;

	int mixVolume{ volume * MIX_MAX_VOLUME };

	Mix_VolumeChunk(sound->second, mixVolume);
	auto channel{ std::async(std::launch::async, Mix_PlayChannel, -1, sound->second, 0) };
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
