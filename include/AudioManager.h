#pragma once
#include <string>
#include <SFML/Audio.hpp>

class AudioManager
{
private:
    sf::Sound m_Sound;
    sf::Music m_Music;

    ~AudioManager();
    AudioManager();

public:
    AudioManager(AudioManager const& copy) = delete;
    AudioManager& operator=(AudioManager const& copy) = delete;
    
    static AudioManager& getInstance();

    sf::Sound& getSoundBuffer();
    void playSound(const sf::SoundBuffer& buffer);
    sf::Music& getMusic();
    void playMusic(const std::string& path, const bool loop = true);
};
