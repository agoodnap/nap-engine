#include "BoxCollisionComponent.h"
#include "GameObject.h"

BoxCollisionComponent::BoxCollisionComponent(GameObject& parent) : GameComponent(parent), m_isTrigger(false)
{
}

sf::FloatRect BoxCollisionComponent::getShape() const
{
    return m_bounds;
}

bool BoxCollisionComponent::isTrigger() const
{
    return m_isTrigger;
}

void BoxCollisionComponent::setIsTrigger(const bool value)
{
    m_isTrigger = value;
}

void BoxCollisionComponent::setSize(const float width, const float height)
{
    m_bounds.width = width;
    m_bounds.height = height;
    m_debugShape->setSize(width, height);
}

void BoxCollisionComponent::update(const float deltaTime)
{
    m_bounds.left = m_parent.getPosition().x - m_bounds.width * 0.5f;
    m_bounds.top = m_parent.getPosition().y - m_bounds.height * 0.5f;
}
