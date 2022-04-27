#pragma once

class RigidBodyComponent;

class CollisionListener
{
public:
    virtual ~CollisionListener() = default;
    virtual void handleCollision(const RigidBodyComponent& body, const RigidBodyComponent& other) = 0;
};
