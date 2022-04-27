#include "SpriteComponent.h"

#include <utility>
#include "GameObject.h"

SpriteComponent::SpriteComponent(GameObject& parent) : RenderComponent(parent),
                                                       m_texture(nullptr), m_sprite(std::make_shared<sf::Sprite>()),
                                                       m_rotateWithParent(true)
{
}

SpriteComponent::~SpriteComponent()
= default;

void SpriteComponent::update(const float deltaTime)
{
    m_sprite->setPosition(m_parent.getPosition());
    if (m_rotateWithParent)
    {
        m_sprite->setRotation(m_parent.getRotation());
    }
}

void SpriteComponent::setScale(const float x, const float y) const
{
    sf::Vector2f newScale;
    newScale.x = x;
    newScale.y = y;
    m_sprite->setScale(newScale);
}

void SpriteComponent::setSmooth(const bool value) const
{
    m_texture->setSmooth(value);
}

void SpriteComponent::setTexture(std::shared_ptr<sf::Texture> texture)
{
    m_texture = std::move(texture);
    m_sprite->setTexture(*m_texture);
}

void SpriteComponent::setColor(sf::Color color) const
{
    m_sprite->setColor(color);
}

std::shared_ptr<sf::Texture> SpriteComponent::getTexture()
{
    return m_texture;
}

void SpriteComponent::setOrigin(const float x, const float y) const
{
    m_sprite->setOrigin(x, y);
}

sf::Vector2f SpriteComponent::getOrigin() const
{
    return m_sprite->getOrigin();
}

std::shared_ptr<sf::Sprite> SpriteComponent::getSprite()
{
    return m_sprite;
}

void SpriteComponent::setRotateWithParent(const bool val)
{
    m_rotateWithParent = val;
}

bool SpriteComponent::rotatesWithParent() const
{
    return m_rotateWithParent;
}

std::vector<std::weak_ptr<sf::Drawable>> SpriteComponent::getDrawables()
{
    std::vector<std::weak_ptr<sf::Drawable>> result;
    const std::weak_ptr<sf::Drawable> weakSpr = m_sprite;
    result.push_back(weakSpr);
    return result;
}
