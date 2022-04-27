#pragma once

class GameObject;

class GameComponent
{
protected:
    GameObject& m_parent;

public:
    virtual ~GameComponent() = default;

    GameComponent(GameObject& parent) : m_parent(parent)
    {
    };

    virtual void update(const float deltaTime) = 0;

    GameObject& getParent() const;
};
