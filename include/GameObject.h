#pragma once

#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include "SFML/Graphics.hpp"
#include "GameComponent.h"
#include "Renderer.h"
#include "PhysicsManager.h"
#include "RigidBodyComponent.h"

#include <type_traits>
#include <vector>

class RenderComponent;

class GameObject : public sf::Transformable
{
private:
    std::string m_name;
    std::map<std::string, std::shared_ptr<GameComponent>> m_gameComponents{};
    bool m_isEnabled;

public:
    GameObject(std::string name);
    ~GameObject() override;
    void update(float deltaTime) const;

    template <class T>
    std::shared_ptr<T> addComponent(const std::string& name)
    {
        static_assert(std::is_base_of<GameComponent, T>::value, "Components must inherit from GameComponent!");

        if (m_gameComponents.find(name) != m_gameComponents.end())
        {
            throw std::invalid_argument("Component with name " + name + " already exists!");
        }

        std::shared_ptr<T> newComponent = std::make_shared<T>(T(*this));
        m_gameComponents.insert({name, newComponent});

        if (std::is_base_of<RenderComponent, T>::value)
        {
            Renderer::getInstance().registerRenderComponent(std::dynamic_pointer_cast<RenderComponent>(newComponent));
        }
        else if (std::is_base_of<RigidBodyComponent, T>::value)
        {
            PhysicsManager::getInstance().
                registerRigidBody(std::dynamic_pointer_cast<RigidBodyComponent>(newComponent));
        }

        return newComponent;
    }

    template <class T>
    std::shared_ptr<T> getComponent(const std::string& name)
    {
        static_assert(std::is_base_of<GameComponent, T>::value, "Components must inherit from GameComponent!");
        if (m_gameComponents.find(name) == m_gameComponents.end())
        {
            return nullptr;
        }
        for (auto i : m_gameComponents)
        {
            if (std::dynamic_pointer_cast<T>(i.second) && i.first == name)
            {
                return std::dynamic_pointer_cast<T>(i.second);
            }
        }

        return nullptr;
    }

    template <class T>
    std::shared_ptr<T> getComponent()
    {
        static_assert(std::is_base_of<GameComponent, T>::value, "Components must inherit from GameComponent!");

        for (auto i : m_gameComponents)
        {
            if (std::dynamic_pointer_cast<T>(i.second))
            {
                return std::dynamic_pointer_cast<T>(i.second);
            }
        }

        return nullptr;
    }

    template <class T>
    std::vector<std::shared_ptr<T>> getComponents()
    {
        static_assert(std::is_base_of<GameComponent, T>::value, "Components must inherit from GameComponent!");

        std::vector<std::shared_ptr<T>> gameComponents;

        for (auto i : m_gameComponents)
        {
            if (std::dynamic_pointer_cast<T>(i.second))
            {
                gameComponents.push_back(std::dynamic_pointer_cast<T>(i.second));
            }
        }

        return gameComponents;
    }

    std::string getName() const;
    bool isEnabled() const;
    bool setIsEnabled(const bool& value);

    sf::Vector2f getVectorBetween(const GameObject& other) const;
    sf::Vector2f getVectorBetween(std::shared_ptr<GameObject> other) const;
};
