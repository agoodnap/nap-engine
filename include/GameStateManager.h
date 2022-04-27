#pragma once

#include <map>
#include <memory>
#include <string>

#include "State.h"

class GameStateManager
{
private:
    std::map<std::string, std::shared_ptr<State>> m_states;
    std::shared_ptr<State> m_currentState;

    bool m_isPaused;

    ~GameStateManager();

    GameStateManager() : m_states(), m_currentState(nullptr), m_isPaused(false)
    {
    }

public:
    GameStateManager(GameStateManager const& copy) = delete;
    GameStateManager& operator=(GameStateManager const& copy) = delete;

    static GameStateManager& getInstance();
    bool init(const std::string& startStateName);
    bool isRunning() const;
    void update(const float deltaTime);
    void exit() const;
    bool setState(const std::string& stateName);
    std::shared_ptr<State> getCurrentState();

    void setPaused(bool value);
    bool isPaused() const;

    template <class T>
    void addState(const std::string name)
    {
        static_assert(std::is_base_of<State, T>::value, "GameStates must inherit from State!");

        if (m_states.find(name) != m_states.end())
        {
            throw "State with name '" + name + "' already instantiated.";
        }

        std::shared_ptr<State> state = std::make_shared<T>(T());
        m_states.insert(std::pair<std::string, std::shared_ptr<State>>(name, state));
    }
};
