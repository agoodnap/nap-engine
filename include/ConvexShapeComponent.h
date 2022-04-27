#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "ShapeComponent.h"

class ConvexShapeComponent : public ShapeComponent
{
private:
    std::shared_ptr<sf::ConvexShape> m_shape;

public:
    ConvexShapeComponent(GameObject& parent);
    ~ConvexShapeComponent() override;

    void setPointCount(const int& count);
    int getPointCount() const;

    void setPoint(const int& index, const sf::Vector2f pos) const;
    sf::Vector2f getPoint(const int& index) const;

    virtual void update(const float deltaTime) override;
    virtual void setScale(const float x, const float y) override;
    virtual void setSmooth(const bool value) override;
    virtual void setTexture(std::shared_ptr<sf::Texture> texture);
    virtual void setFillColor(sf::Color color) override;
    virtual void setOutlineColor(sf::Color color) override;
    virtual void setOutlineThickness(const float value) override;
    virtual void setOrigin(const float x, const float y) override;
    virtual void setRotation(const float angle) override;

    virtual std::shared_ptr<sf::Shape> getShape() override;
    virtual std::vector<std::weak_ptr<sf::Drawable>> getDrawables() override;
};
