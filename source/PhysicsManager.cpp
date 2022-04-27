#include "BoxCollisionComponent.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "RigidBodyComponent.h"

PhysicsManager& PhysicsManager::getInstance()
{
    static PhysicsManager instance;
    return instance;
}

PhysicsManager::PhysicsManager() : m_rigidBodies(), m_accumulator()
{
}

PhysicsManager::~PhysicsManager()
{
    m_rigidBodies.clear();
}

void PhysicsManager::update(const float deltaTime)
{
    m_accumulator += deltaTime;

    while (m_accumulator > m_step)
    {
        m_manifolds.clear();
        findCollisions();
        resolveCollisions();
        m_accumulator -= m_step;
    }
}

void PhysicsManager::registerRigidBody(const std::weak_ptr<RigidBodyComponent>& rb)
{
    m_rigidBodies.push_back(rb);
}

void PhysicsManager::findCollisions()
{
    for (auto expiredItr = m_rigidBodies.begin(); expiredItr != m_rigidBodies.end();)
    {
        if (auto valid = expiredItr->lock())
        {
            ++expiredItr;
        }
        else
        {
            expiredItr = m_rigidBodies.erase(expiredItr);
        }
    }

    for (auto itA = m_rigidBodies.begin(); itA != m_rigidBodies.end(); ++itA)
    {
        if (auto body1 = itA->lock())
        {
            if (!body1->getParent().isEnabled())
            {
                continue;
            }

            for (auto itB = itA; itB != m_rigidBodies.end(); ++itB)
            {
                if (auto body2 = itB->lock())
                {
                    if (!body2->getParent().isEnabled())
                    {
                        continue;
                    }

                    if (body1 == body2)
                    {
                        continue;
                    }

                    // if both object don't have a mass or body is the same skip
                    if (body1->getMass() == 0 && body2->getMass() == 0)
                    {
                        continue;
                    }

                    sf::Transform body1Transform;
                    body1Transform.translate(body1->getPosition());
                    sf::Transform body2Transform;
                    body2Transform.translate(body2->getPosition());

                    sf::Vector2f normal;
                    float penetration;
                    auto body1Colliders = body1->getColliders();
                    auto body2Colliders = body2->getColliders();
                    bool collisionFound = false;
                    for (const auto& col1 : body1Colliders)
                    {
                        if (collisionFound)
                        {
                            break;
                        }

                        for (const auto& col2 : body2Colliders)
                        {
                            if (collisionFound)
                            {
                                break;
                            }

                            if (AABBvsAABB(body1Transform.transformRect(col1->getShape()),
                                           body2Transform.transformRect(col2->getShape()),
                                           normal,
                                           penetration))
                            {
                                Manifold manifold;
                                manifold.body1 = body1;
                                manifold.body2 = body2;
                                manifold.normal = normal;
                                manifold.penetration = penetration;

                                if (col1->isTrigger() || col2->isTrigger())
                                {
                                    manifold.doPhysicsResponse = false;
                                }

                                m_manifolds.push_back(manifold);

                                collisionFound = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void PhysicsManager::resolveCollisions() const
{
    for (const auto& man : m_manifolds)
    {
        // Calculate relative velocity
        auto body1 = man.body1.lock();
        auto body2 = man.body2.lock();

        if (!body1 || !body2)
        {
            continue;
        }
        body1->onCollision(*body2);
        body2->onCollision(*body1);

        if (!man.doPhysicsResponse)
            continue;

        if (body1->getInvMass() == 0 && body2->getInvMass() == 0)
            continue;

        const sf::Vector2f rv = body1->getVelocity() - body2->getVelocity();

        // Calculate relative velocity in terms of the normal direction (length through vector projection)
        const float velAlongNormal = rv.x * man.normal.x + rv.y * man.normal.y;

        // Do not resolve if velocities are separating
        if (velAlongNormal > 0)
        {
            return;
        }

        if (body1->getBounciness() > 0 || body2->getBounciness() > 0)
        {
            // Calculate impulse scalar
            const float e = (body1->getBounciness() + body2->getBounciness()) * 0.5f; ///< 1.0 = all objects are bouncy
            float j = -(1 + e) * velAlongNormal;
            j /= body1->getInvMass() + body2->getInvMass();

            // Apply impulse
            sf::Vector2f impulse = j * man.normal;

            // impulse proportional to mass
            body1->setVelocity(body1->getVelocity() + body1->getInvMass() * impulse);
            body2->setVelocity(body2->getVelocity() - body2->getInvMass() * impulse);
        }
        else
        {
            // Apply impulse
            sf::Vector2f impulse = velAlongNormal * man.normal;

            body1->setVelocity(body1->getVelocity() - body1->getInvMass() * impulse);
            body2->setVelocity(body2->getVelocity() + body2->getInvMass() * impulse);
        }

        // Positional correction
        constexpr float percent = 0.2f; // usually 20% to 80%
        constexpr float slop = 0.01f; // usually 0.01 to 0.1
        sf::Vector2f correction = std::max(man.penetration - slop, 0.0f) /
            (body1->getInvMass() + body2->getInvMass()) * percent * man.normal;
        // Apply directly to position
        body1->setPosition(body1->getPosition() + body1->getInvMass() * correction);
        body2->setPosition(body2->getPosition() + body2->getInvMass() * correction);
    }
}

bool PhysicsManager::AABBvsAABB(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration) const
{
    auto getCenter = [](const sf::FloatRect& rect) -> sf::Vector2f
    {
        const auto result = sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height);
        return result;
    };

    const sf::Vector2f n = getCenter(b) - getCenter(a); // Vector from A to B
    float a_extent = a.width * 0.5f; // Calculate half extents along x axis
    float b_extent = b.width * 0.5f;
    const float x_overlap = a_extent + b_extent - abs(n.x) * 0.5f; // Calculate overlap on x axis
    if (x_overlap > 0)
    {
        // SAT test on x axis
        a_extent = a.height * 0.5f; // Calculate half extents along y axis
        b_extent = b.height * 0.5f;
        const float y_overlap = a_extent + b_extent - abs(n.y) * 0.5f; // Calculate overlap on y axis
        if (y_overlap > 0)
        {
            // SAT test on y axis
            if (x_overlap < y_overlap)
            {
                // Find out which axis is axis of least penetration
                if (n.x < 0) // Point towards B knowing that n points from A to B
                    normal = sf::Vector2f(1.0f, 0.0f);
                else
                    normal = sf::Vector2f(-1.0f, 0.0f);
                penetration = x_overlap;
                return true;
            }
            else
            {
                if (n.y < 0) // Point towards B knowing that n points from A to B
                    normal = sf::Vector2f(0, 1);
                else
                    normal = sf::Vector2f(0, -1);
                penetration = y_overlap;
                return true;
            }
        }
    }
    return false;
}
