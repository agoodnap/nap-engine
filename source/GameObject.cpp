#include "GameObject.h"

GameObject::GameObject(std::string name) : m_name(std::move(name)), m_gameComponents(), m_isEnabled(true)
{
}

GameObject::~GameObject()
{
    m_gameComponents.clear();
}

void GameObject::update(float deltaTime) const
{
    if (m_isEnabled)
    {
        for (auto&& component : m_gameComponents)
        {
            component.second->update(deltaTime);
        }
    }
}

std::string GameObject::getName() const
{
    return m_name;
}

bool GameObject::isEnabled() const
{
    return m_isEnabled;
}

bool GameObject::setIsEnabled(const bool& value)
{
    return m_isEnabled = value;
}

sf::Vector2f GameObject::getVectorBetween(const GameObject& other) const
{
    return other.getPosition() - getPosition();
}

sf::Vector2f GameObject::getVectorBetween(const std::shared_ptr<GameObject>& other) const
{
    return other->getPosition() - getPosition();
}
