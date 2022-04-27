#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "GameComponent.h"

#include "RectShapeComponent.h"

class RigidBodyComponent;

class BoxCollisionComponent : public GameComponent
{
private:
    sf::FloatRect m_bounds;
    std::shared_ptr<RectShapeComponent> m_debugShape;
    bool m_isTrigger;

public:
    BoxCollisionComponent(GameObject& parent);
    void setSize(const float width, const float height);
    sf::FloatRect getShape() const;
    bool isTrigger() const;
    void setIsTrigger(const bool value);
    virtual void update(const float deltaTime) override;
};
