#include "BoxCollisionComponent.h"
#include "GameObject.h"

#include "Renderer.h"

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

BoxCollisionComponent::BoxCollisionComponent(GameObject& parent) : GameComponent(parent), m_debugShape(std::make_shared<RectShapeComponent>(parent)), m_isTrigger(false)
{
	m_debugShape->setRotateWithParent(false);
	m_debugShape->setFillColor((sf::Color::Transparent));
	m_debugShape->setOutlineColor(sf::Color::Green);
	m_debugShape->setOutlineThickness(1);
	m_debugShape->setRenderOrder(10000);
	//Render.registerRenderComponent(m_debugShape);//change for debug collision
}

void BoxCollisionComponent::update(const float deltaTime)
{
	m_bounds.left = m_parent.getPosition().x - m_bounds.width * 0.5f;
	m_bounds.top = m_parent.getPosition().y - m_bounds.height * 0.5f;
	m_debugShape->setPosition(m_bounds.left, m_bounds.top);
	m_debugShape->setSize(m_bounds.width, m_bounds.height);
}
