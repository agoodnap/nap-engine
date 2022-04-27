#include "CameraComponent.h"
#include "GameObject.h"

void CameraComponent::zoom(const float factor)
{
	m_view.zoom(factor);
}

void CameraComponent::rotate(const float angle)
{
	m_view.rotate(angle);
}

void CameraComponent::update(float deltaTime)
{
	m_view.setCenter(m_parent.getPosition());

}

void CameraComponent::setSize(const float width, const float height)
{
	m_view.setSize(width, height);
	m_view.setCenter(width / 2, height / 2);
}

sf::View& CameraComponent::getView()
{
	return m_view;
}

