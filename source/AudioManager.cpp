#include "AudioManager.h"

#include <string>

using namespace sf;

AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{
	m_Sound.stop();
	m_Music.stop();
}

AudioManager& AudioManager::getInstance()
{
	static AudioManager instance;
	return instance;
}

Sound& AudioManager::getSoundBuffer()
{
	return m_Sound;
}

void AudioManager::playSound(const SoundBuffer& buffer)
{
	m_Sound.stop();
	m_Sound.setBuffer(buffer);
	m_Sound.setVolume(20);
	m_Sound.play();
}

Music& AudioManager::getMusic()
{
	return m_Music;
}

void AudioManager::playMusic(const std::string& path, const bool loop)
{
	m_Music.stop();
	if (m_Music.openFromFile(path)) 
	{
		m_Music.setLoop(loop);
		m_Music.play();
	}
}

