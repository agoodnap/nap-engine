#include "Game.h"

#include <stdexcept>
#include <SFML/Graphics.hpp>

#include "Renderer.h"


void Game::startGame(const std::string& startState, const unsigned int windowX, const unsigned int windowY,
                     const std::string
                     & name)
{
    if (isRunning())
    {
        throw std::exception("Game is already running.");
    }

    if (!GameStateManager::getInstance().init(startState))
    {
        throw std::invalid_argument(
            "Could not initialize game with state '" + startState + "'. Did you add the state beforehand?");
    }

    if (!Renderer::getInstance().initWindow(windowX, windowY, name))
    {
        return;
    }

    while (GameStateManager::getInstance().isRunning())
    {
        static sf::Clock clock;
        sf::Time deltaTime = clock.restart();
        GameStateManager::getInstance().update(deltaTime.asSeconds());
    }
}

bool Game::isRunning()
{
    return GameStateManager::getInstance().isRunning();
}
