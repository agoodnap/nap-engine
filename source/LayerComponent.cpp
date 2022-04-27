#include "LayerComponent.h"

LayerComponent::LayerComponent(GameObject& parent) : RenderComponent(parent), m_sprites(), m_width(0), m_height(0)
{
}

LayerComponent::~LayerComponent()
= default;

void LayerComponent::update(float deltaTime)
{
}

void LayerComponent::add(std::shared_ptr<sf::Sprite> sprite)
{
    m_sprites.push_back(sprite);
}

int LayerComponent::getWidth() const
{
    return m_width;
}

void LayerComponent::setWidth(const int& width)
{
    m_width = width;
}

int LayerComponent::getHeight() const
{
    return m_height;
}

void LayerComponent::setHeight(const int& height)
{
    m_height = height;
}

std::vector<std::weak_ptr<sf::Drawable>> LayerComponent::getDrawables()
{
    std::vector<std::weak_ptr<sf::Drawable>> result;
    for (auto sprite : m_sprites)
    {
        std::weak_ptr<sf::Drawable> weakSpr = sprite;
        result.push_back(weakSpr);
    }
    return result;
}
