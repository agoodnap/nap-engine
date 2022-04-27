#include "ResourceManager.h"

#include <iostream>

#include "LayerComponent.h"

using namespace sf;

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager()
= default;

ResourceManager::~ResourceManager()
{
    m_textureCache.clear();
    m_soundCache.clear();
}

bool ResourceManager::loadTexture(const std::string& id, const std::string& path, const IntRect& area)
{
    std::shared_ptr<Texture> newTex = std::make_shared<Texture>();
    if (!newTex->loadFromFile(path, area))
    {
        return false;
    }

    m_textureCache.add(id, newTex);
    return true;
}

void ResourceManager::freeTexture(const std::string id)
{
    if (m_textureCache.get(id))
    {
        m_textureCache.erase(id);
    }
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& id)
{
    return m_textureCache.get(id);
}

bool ResourceManager::loadSoundBuffer(const std::string& id, const std::string& path)
{
    std::shared_ptr<SoundBuffer> newSound = std::make_shared<SoundBuffer>();
    if (!newSound->loadFromFile(path))
    {
        std::cout << "Error while loading music" << std::endl;
        std::cout << path << std::endl;
        return false;
    }

    m_soundCache.add(id, newSound);
    return true;
}

void ResourceManager::freeSoundBuffer(const std::string& id)
{
    if (m_soundCache.get(id))
    {
        m_soundCache.erase(id);
    }
}

std::shared_ptr<SoundBuffer> ResourceManager::getSoundBuffer(const std::string& id)
{
    return m_soundCache.get(id);
}
