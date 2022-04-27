#pragma once

#include "GameComponent.h"

class BoxCollisionComponent;
class CollisionListener;

class RigidBodyComponent : public GameComponent
{
private:
    float m_mass;
    float m_invMass;

    float m_bounciness; //keep between 0 and 1

    float m_maxSpeed;

    sf::Vector2f m_acceleration{};
    sf::Vector2f m_velocity{};

    std::vector<sf::Vector2f> m_forces{};
    std::vector<sf::Vector2f> m_impulses{};

    std::vector<std::weak_ptr<CollisionListener>> m_listeners{};

public:
    RigidBodyComponent(GameObject& parent) : GameComponent(parent), m_mass(0), m_invMass(0), m_bounciness(0),
                                             m_maxSpeed(0)
    {
    }
    virtual void update(const float deltaTime) override;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f position) const;
    void setMass(const float& mass);
    float getMass() const;
    float getInvMass() const;
    float getMaxSpeed() const;
    sf::Vector2f getAcceleration() const;
    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& velocity);
    void setBounciness(const float& bounciness);
    void setMaxSpeed(const float& speed);
    float getBounciness() const;
    void addForce(const sf::Vector2f& force);
    void addImpulse(const sf::Vector2f& impulse);

    void registerListener(const std::shared_ptr<CollisionListener>& listener);
    void onCollision(const RigidBodyComponent& other);


    std::vector<std::shared_ptr<BoxCollisionComponent>> getColliders() const;
};
