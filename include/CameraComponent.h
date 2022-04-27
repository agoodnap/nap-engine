#pragma once
#include <SFML/Graphics.hpp>

#include "GameComponent.h"

class CameraComponent : public GameComponent
{
private:
    sf::View m_view{};

public:
    explicit CameraComponent(GameObject& parent) : GameComponent(parent)
    {
    }

    void zoom(const float factor);
    void rotate(const float angle);
    void update(const float deltaTime) override;
    void setSize(const float width, const float height);
    sf::View& getView();
};
