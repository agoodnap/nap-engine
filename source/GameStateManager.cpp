#include "GameStateManager.h"
#include "Renderer.h"
#include "PhysicsManager.h"

GameStateManager& GameStateManager::getInstance()
{
    static GameStateManager instance;
    return instance;
}

GameStateManager::~GameStateManager()
{
    m_states.clear();
    m_currentState = nullptr;
}

bool GameStateManager::init(const std::string& startStateName)
{
    return setState(startStateName);
}

bool GameStateManager::isRunning() const
{
    return Renderer::getInstance().isWindowOpen() && m_currentState != nullptr;
}

void GameStateManager::update(float deltaTime) const
{
    sf::Event event{};
    while (Renderer::getInstance().pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            Renderer::getInstance().closeWindow();
            exit();
            return;
        }
    }

    Renderer::getInstance().clear();

    if (!m_isPaused)
    {
        if (m_currentState)
        {
            m_currentState->update(deltaTime);
            m_currentState->State::update(deltaTime);
        }
        PhysicsManager::getInstance().update(deltaTime);
    }

    Renderer::getInstance().display();
}

void GameStateManager::exit() const
{
    Renderer::getInstance().closeWindow();
    m_currentState->exit();
}

bool GameStateManager::setState(const std::string& stateName)
{
    if (m_states.find(stateName) == m_states.end())
    {
        return false;
    }

    const auto state = m_states[stateName];

    if (state != m_currentState)
    {
        if (m_currentState != nullptr)
        {
            m_currentState->exit();
        }

        m_isPaused = false;

        Renderer::getInstance().cullExpiredComponents();

        m_currentState = state;

        return m_currentState->init();
    }
    return true;
}

std::shared_ptr<State> GameStateManager::getCurrentState()
{
    return m_currentState;
}

void GameStateManager::setPaused(bool value)
{
    m_isPaused = value;
}

bool GameStateManager::isPaused() const
{
    return m_isPaused;
}
