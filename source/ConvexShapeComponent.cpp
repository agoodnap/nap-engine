#include "ConvexShapeComponent.h"
#include "GameObject.h"

using namespace sf;

ConvexShapeComponent::ConvexShapeComponent(GameObject& parent) : ShapeComponent(parent),
                                                                 m_shape(std::make_shared<sf::ConvexShape>())
{
}

ConvexShapeComponent::~ConvexShapeComponent()
= default;

void ConvexShapeComponent::setPointCount(const int& count)
{
    if (m_shape)
        m_shape->setPointCount(count);
}

int ConvexShapeComponent::getPointCount() const
{
    if (m_shape)
    {
        return m_shape->getPointCount();
    }
    else
    {
        return -1;
    }
}

void ConvexShapeComponent::setPoint(const int& index, const sf::Vector2f pos) const
{
    if (m_shape)
    {
        m_shape->setPoint(index, pos);
    }
}

sf::Vector2f ConvexShapeComponent::getPoint(const int& index) const
{
    if (m_shape)
    {
        return m_shape->getPoint(index);
    }
    else
    {
        return {};
    }
}

std::shared_ptr<sf::Shape> ConvexShapeComponent::getShape()
{
    return m_shape;
}

void ConvexShapeComponent::update(const float deltaTime)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setPosition(m_parent.getPosition());

    if (m_rotateWithParent)
    {
        m_shape->setRotation(m_parent.getRotation());
    }
}

void ConvexShapeComponent::setScale(const float x, const float y)
{
    if (m_shape)
    {
        sf::Vector2f newScale;
        newScale.x = x;
        newScale.y = y;
        m_shape->setScale(newScale);
    }
}

void ConvexShapeComponent::setSmooth(const bool value)
{
    if (m_texture)
    {
        m_texture->setSmooth(value);
    }
}

void ConvexShapeComponent::setTexture(std::shared_ptr<sf::Texture> texture)
{
    ShapeComponent::setTexture(texture);

    if (!m_shape)
    {
        return;
    }

    m_shape->setTexture(m_texture.get());
}

void ConvexShapeComponent::setFillColor(sf::Color color)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setFillColor(color);
}

void ConvexShapeComponent::setOutlineColor(sf::Color color)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setOutlineColor(color);
}

void ConvexShapeComponent::setOutlineThickness(const float value)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setOutlineThickness(value);
}

void ConvexShapeComponent::setOrigin(const float x, const float y)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setOrigin(x, y);
}

void ConvexShapeComponent::setRotation(const float angle)
{
    m_shape->setRotation(angle);
}

std::vector<std::weak_ptr<sf::Drawable>> ConvexShapeComponent::getDrawables()
{
    std::vector<std::weak_ptr<sf::Drawable>> result;
    const std::weak_ptr<sf::Drawable> weakP = m_shape;
    result.push_back(weakP);
    return result;
}
