#include "BoxCollisionComponent.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "CollisionListener.h"

using namespace sf;

void RigidBodyComponent::update(float deltaTime)
{
    Vector2f forces{};
    for (const auto& f : m_forces)
        forces += f;

    for (const auto& i : m_impulses)
        forces += i;
    m_impulses.clear();

    // symplectic Euler
    m_acceleration = forces * m_invMass;
    m_velocity += m_acceleration * deltaTime;
    setPosition(getPosition() + m_velocity * deltaTime);
}

sf::Vector2f RigidBodyComponent::getPosition() const
{
    return m_parent.getPosition();
}

void RigidBodyComponent::setPosition(const sf::Vector2f position)
{
    m_parent.setPosition(position);
}

void RigidBodyComponent::setMass(const float& mass)
{
    m_mass = mass;
    if (m_mass == 0)
        m_invMass = 0;
    else
        m_invMass = 1 / m_mass;
}

float RigidBodyComponent::getMass() const
{
    return m_mass;
}

float RigidBodyComponent::getInvMass() const
{
    return m_invMass;
}

float RigidBodyComponent::getMaxSpeed() const
{
    return m_maxSpeed;
}

sf::Vector2f RigidBodyComponent::getAcceleration() const
{
    return m_acceleration;
}

sf::Vector2f RigidBodyComponent::getVelocity() const
{
    return m_velocity;
}

void RigidBodyComponent::setVelocity(const sf::Vector2f& velocity)
{
    m_velocity = velocity;
}

void RigidBodyComponent::setBounciness(const float& bounciness)
{
    m_bounciness = bounciness;
}

void RigidBodyComponent::setMaxSpeed(const float& speed)
{
    m_maxSpeed = speed;
}

float RigidBodyComponent::getBounciness() const
{
    return m_bounciness;
}

void RigidBodyComponent::addForce(const sf::Vector2f& force)
{
    m_forces.push_back(force);
}

void RigidBodyComponent::addImpulse(const sf::Vector2f& impulse)
{
    auto length2 = [](const sf::Vector2f& vec)-> float { return vec.x * vec.x + vec.y * vec.y; };
    if (length2(m_velocity + impulse) < m_maxSpeed * m_maxSpeed)
    {
        m_impulses.push_back(impulse);
    }
}


void RigidBodyComponent::registerListener(const std::shared_ptr<CollisionListener> listener)
{
    m_listeners.push_back(listener);
}

void RigidBodyComponent::onCollision(const RigidBodyComponent& other)
{
    for (auto itr = m_listeners.begin(); itr != m_listeners.end();)
    {
        if (const auto listener = itr->lock())
        {
            listener->handleCollision(*this, other);
            ++itr;
        }
        else
        {
            itr = m_listeners.erase(itr);
        }
    }
}

std::vector<std::shared_ptr<BoxCollisionComponent>> RigidBodyComponent::getColliders() const
{
    return m_parent.getComponents<BoxCollisionComponent>();
}
