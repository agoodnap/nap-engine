#pragma once

#include <SFML/Audio.hpp>

#include "ResourceDataCache.h"
#include "GameObject.h"

class ResourceManager
{
private:
    ResourceDataCache<sf::Texture> m_textureCache{};
    ResourceDataCache<sf::SoundBuffer> m_soundCache{};

    ~ResourceManager();
    ResourceManager();
public:
    ResourceManager(ResourceManager const& copy) = delete;
    ResourceManager& operator=(ResourceManager const& copy) = delete;
    
    static ResourceManager& getInstance();

    bool loadTexture(const std::string& id, const std::string& path, const sf::IntRect& area = sf::IntRect());
    void freeTexture(const std::string& id);
    std::shared_ptr<sf::Texture> getTexture(const std::string& id);

    bool loadSoundBuffer(const std::string& id, const std::string& path);
    void freeSoundBuffer(const std::string& id);
    std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string& id);
};
