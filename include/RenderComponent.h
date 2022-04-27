#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "GameComponent.h"

class RenderComponent : public GameComponent
{
private:
    int m_renderOrder;

public:
    RenderComponent(GameObject& parent) : GameComponent(parent), m_renderOrder(0)
    {
    }

    void update(float deltaTime) override = 0;
    virtual std::vector<std::weak_ptr<sf::Drawable>> getDrawables() = 0;
    int getRenderOrder() const { return m_renderOrder; }
    void setRenderOrder(const int& order) { m_renderOrder = order; }
};
