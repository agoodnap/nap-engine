#include "RectShapeComponent.h"
#include "GameObject.h"

using namespace sf;

RectShapeComponent::RectShapeComponent(GameObject& parent) : ShapeComponent(parent),
                                                             m_shape(std::make_shared<sf::RectangleShape>())
{
}

RectShapeComponent::~RectShapeComponent()
= default;


void RectShapeComponent::update(const float deltaTime)
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

void RectShapeComponent::setScale(const float x, const float y)
{
    if (m_shape)
    {
        sf::Vector2f newScale;
        newScale.x = x;
        newScale.y = y;;
        m_shape->setScale(newScale);
    }
}

void RectShapeComponent::setSmooth(const bool value)
{
    if (m_texture)
    {
        m_texture->setSmooth(value);
    }
}

void RectShapeComponent::setTexture(std::shared_ptr<sf::Texture> texture)
{
    ShapeComponent::setTexture(texture);

    if (!m_shape)
    {
        return;
    }

    m_shape->setTexture(m_texture.get());
}

void RectShapeComponent::setFillColor(sf::Color color)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setFillColor(color);
}

void RectShapeComponent::setOutlineColor(sf::Color color)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setOutlineColor(color);
}

void RectShapeComponent::setOutlineThickness(const float value)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setOutlineThickness(value);
}

void RectShapeComponent::setOrigin(const float x, const float y)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setOrigin(x, y);
}

void RectShapeComponent::setRotation(const float angle)
{
    m_shape->setRotation(angle);
}

void RectShapeComponent::setPosition(const float x, const float y)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setPosition(x, y);
}

void RectShapeComponent::setSize(const float width, const float height)
{
    if (!m_shape)
    {
        return;
    }

    m_shape->setSize(sf::Vector2f(width, height));
}

std::shared_ptr<sf::Shape> RectShapeComponent::getShape()
{
    return m_shape;
}

std::vector<std::weak_ptr<sf::Drawable>> RectShapeComponent::getDrawables()
{
    std::vector<std::weak_ptr<sf::Drawable>> result;
    std::weak_ptr<sf::Drawable> weakP = m_shape;
    result.push_back(weakP);
    return result;
}
