#include "GameObjectManager.h"

GameObjectManager& GameObjectManager::getInstance()
{
    static GameObjectManager instance;
    return instance;
}

GameObjectManager::GameObjectManager() : m_gameObjects()
{
}

GameObjectManager::~GameObjectManager()
{
    m_gameObjects.clear();
}

std::weak_ptr<GameObject> GameObjectManager::addGameObject(const std::string& name)
{
    int i = 1;
    std::string curName = name;
    while (m_gameObjects.find(curName) != m_gameObjects.end())
    {
        curName = name + std::to_string(i++);
    }

    auto newObjPtr = std::make_shared<GameObject>(curName);
    m_gameObjects.insert({curName, newObjPtr});
    return newObjPtr;
}

std::weak_ptr<GameObject> GameObjectManager::addGameObject(const std::shared_ptr<GameObject>& newObject)
{
    if (m_gameObjects.find(newObject->getName()) != m_gameObjects.end())
    {
        throw std::invalid_argument("Component with name " + newObject->getName() + " already exists!");
    }

    m_gameObjects.insert({newObject->getName(), newObject});
    return newObject;
}

std::weak_ptr<GameObject> GameObjectManager::getGameObject(const std::string& name)
{
    return m_gameObjects[name];
}

std::vector<std::weak_ptr<GameObject>> GameObjectManager::getGameObjects() const
{
    std::vector<std::weak_ptr<GameObject>> returnVector;
    for (const auto& obj : m_gameObjects)
    {
        returnVector.push_back(obj.second);
    }

    return returnVector;
}

std::vector<std::weak_ptr<GameObject>> GameObjectManager::getGameObjectsByName(std::string name) const
{
    std::vector<std::weak_ptr<GameObject>> returnVector;
    for (const auto& obj : m_gameObjects)
    {
        if (obj.first.find(name) != std::string::npos)
        {
            returnVector.push_back(obj.second);
        }
    }

    return returnVector;
}

void GameObjectManager::deleteGameObject(const std::string& name)
{
    m_gameObjects.erase(name);
}

void GameObjectManager::clearGameObjects()
{
    m_gameObjects.clear();
}
