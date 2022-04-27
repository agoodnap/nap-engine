#include "State.h"
#include "GameObjectManager.h"

void State::update(const float deltaTime)
{
	for (const auto& gameObj : GameObjectManager::getInstance().getGameObjects()) 
	{
		if (const auto obj = gameObj.lock()) 
		{
			obj->update(deltaTime);
		}
	}
}

