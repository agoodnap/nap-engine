#pragma once
#include <vector>

#include "GameObject.h"

class GameObjectManager {
private:
	std::map<std::string, std::shared_ptr<GameObject>> m_gameObjects{};

	GameObjectManager();
	~GameObjectManager();

public:
	GameObjectManager(GameObjectManager const& copy) = delete;
	GameObjectManager& operator=(GameObjectManager const& copy) = delete;
	
	static GameObjectManager& getInstance();

	std::weak_ptr<GameObject> addGameObject(const std::string& name);
	std::weak_ptr<GameObject> addGameObject(const std::shared_ptr<GameObject>& newObject);
	std::weak_ptr<GameObject> getGameObject(const std::string& name);
	
	std::vector<std::weak_ptr<GameObject>> getGameObjects() const;
	std::vector < std::weak_ptr<GameObject>> getGameObjectsByName(std::string name) const;
	void deleteGameObject(const std::string& name);
	void clearGameObjects();
};