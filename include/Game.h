#pragma once

#include <string>

#include "State.h"
#include "GameStateManager.h"

class Game
{
public:
    static void startGame(const std::string& startState, const unsigned int windowX = 800, const unsigned int windowY = 600,
                          const std::string& name = "Game");
    static bool isRunning();

    template <class T>
    static void addState(const std::string name)
    {
        static_assert(std::is_base_of<State, T>::value, "GameStates must inherit from State!");

        GameStateManager::getInstance().addState<T>(name);
    }
};
