#include "InputManager.h"

InputManager& InputManager::getInstance()
{
    static InputManager instance;
    return instance;
}

InputManager::InputManager()
= default;

InputManager::~InputManager()
= default;

bool InputManager::isKeyDown(const int keyCode)
{
    if (!keybindExists(keyCode))
    {
        return false;
    }

    const bool keyPressed = m_keyBoard.isKeyPressed(static_cast<sf::Keyboard::Key>(keyCode));
    setKeyPressed(keyCode, keyPressed);
    return keyPressed;
}

bool InputManager::isKeyUp(const int keyCode)
{
    return !isKeyDown(keyCode);
}

bool InputManager::isKeyPressed(const int keyCode)
{
    if (!keybindExists(keyCode))
    {
        return false;
    }

    const bool keyPressedInMap = getKeyPressed(keyCode);
    const bool keyPressedCurrent = m_keyBoard.isKeyPressed(static_cast<sf::Keyboard::Key>(keyCode));
    setKeyPressed(keyCode, keyPressedCurrent);
    if (!keyPressedInMap && keyPressedCurrent)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool InputManager::isKeyReleased(const int keyCode)
{
    if (!keybindExists(keyCode))
    {
        return false;
    }

    const bool keyPressedInMap = getKeyPressed(keyCode);
    const bool keyPressedCurrent = m_keyBoard.isKeyPressed(static_cast<sf::Keyboard::Key>(keyCode));
    setKeyPressed(keyCode, keyPressedCurrent);
    if (keyPressedInMap && !keyPressedCurrent)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool InputManager::isKeyDown(const std::string& action, const int playerIdx)
{
    std::vector<KeyBind> keyBinds;
    findKeybindsForAction(action, playerIdx, keyBinds);
    if (keyBinds.empty())
    {
        return false;
    }

    for (const auto& i : keyBinds)
    {
        if (isKeyDown(i.m_keyCode))
        {
            return true;
        }
    }

    return false;
}

bool InputManager::isKeyUp(const std::string& action, const int playerIdx)
{
    return !isKeyDown(action, playerIdx);
}

bool InputManager::isKeyPressed(const std::string& action, const int playerIdx)
{
    std::vector<KeyBind> keyBinds;
    findKeybindsForAction(action, playerIdx, keyBinds);
    if (keyBinds.empty())
    {
        return false;
    }

    for (const auto& i : keyBinds)
    {
        if (isKeyPressed(i.m_keyCode))
        {
            return true;
        }
    }

    return false;
}

bool InputManager::isKeyReleased(const std::string& action, const int playerIdx)
{
    std::vector<KeyBind> keyBinds;
    findKeybindsForAction(action, playerIdx, keyBinds);
    if (keyBinds.empty())
    {
        return false;
    }

    for (const auto& i : keyBinds)
    {
        if (isKeyReleased(i.m_keyCode))
        {
            return true;
        }
    }
    return false;
}

void InputManager::bind(const std::string& action, const int keyCode, const int playerIdx)
{
    std::vector<KeyBind> keyBinds;
    findKeybindsForAction(action, playerIdx, keyBinds);

    if (!keyBinds.empty())
    {
        for (const auto& i : keyBinds)
        {
            if (i.m_keyCode == keyCode)
            {
                return;
            }
        }
    }

    KeyBind newKeyBind;
    newKeyBind.m_action = action;
    newKeyBind.m_keyCode = keyCode;
    newKeyBind.m_playerIdx = playerIdx;
    m_boundKeys.insert(std::pair<const KeyBind, bool>(newKeyBind, false));
}

void InputManager::unbind(const std::string& action, const int playerIdx)
{
    std::vector<KeyBind> keyBinds;
    findKeybindsForAction(action, playerIdx, keyBinds);

    if (!keyBinds.empty())
    {
        for (const auto& kBind : keyBinds)
        {
            m_boundKeys.erase(kBind);
        }
    }
}

void InputManager::unbind(const int keyCode, const int playerIdx)
{
    KeyBind toRemove;
    for (const auto& it : m_boundKeys)
    {
        if (it.first.m_keyCode == keyCode && it.first.m_playerIdx == playerIdx)
        {
            toRemove = it.first;
        }
    }
    m_boundKeys.erase(toRemove);
}

bool InputManager::keybindExists(const int keyCode)
{
    for (const auto& it : m_boundKeys)
    {
        if (it.first.m_keyCode == keyCode)
        {
            return true;
        }
    }

    return false;
}

void InputManager::findKeybindsForAction(const std::string& action, const int playerIdx, std::vector<KeyBind>& out)
{
    for (const auto& it : m_boundKeys)
    {
        if (it.first.m_action == action && it.first.m_playerIdx == playerIdx)
        {
            out.push_back(it.first);
        }
    }
}

bool InputManager::getKeyPressed(const int keyCode) const
{
    for (const auto& it : m_boundKeys)
    {
        if (it.first.m_keyCode == keyCode)
        {
            return it.second;
        }
    }
    return false;
}

void InputManager::setKeyPressed(const int keyCode, const bool value)
{
    for (const auto& it : m_boundKeys)
    {
        if (it.first.m_keyCode == keyCode)
        {
            m_boundKeys.find(it.first)->second = value;
        }
    }
}
