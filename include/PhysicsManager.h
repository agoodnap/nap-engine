#pragma once

class RigidBodyComponent;

class PhysicsManager
{
private:
    struct Manifold
    {
        std::weak_ptr<RigidBodyComponent> body1;
        std::weak_ptr<RigidBodyComponent> body2;

        bool doPhysicsResponse{};
        float penetration{};
        sf::Vector2f normal;
    };

    std::vector<std::weak_ptr<RigidBodyComponent>> m_rigidBodies{};
    std::vector<Manifold> m_manifolds{};

    const float m_step = 1.0f / 100.0f;
    float m_accumulator;

    ~PhysicsManager();
    PhysicsManager();

    void findCollisions();
    void resolveCollisions();
    bool AABBvsAABB(const sf::FloatRect& a, const sf::FloatRect& b, sf::Vector2f& normal, float& penetration);
public:
    PhysicsManager(PhysicsManager const& copy) = delete;
    PhysicsManager& operator=(PhysicsManager const& copy) = delete;

    static PhysicsManager& getInstance();

    void update(const float deltaTime);
    void registerRigidBody(std::weak_ptr<RigidBodyComponent> rb);
};
