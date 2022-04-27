#pragma once
#include <map>
#include <string>
#include <vector>
#include <SFML/Window/Keyboard.hpp>

class InputManager
{
private:
    struct KeyBind
    {
        std::string m_action;
        int m_keyCode{};
        int m_playerIdx{};

        friend bool operator<(const KeyBind& a, const KeyBind& b)
        {
            return a.m_keyCode < b.m_keyCode;
        }
    };

    sf::Keyboard m_keyBoard{};
    std::map<KeyBind, bool> m_boundKeys;

    InputManager();
    ~InputManager();

    bool keybindExists(const int keyCode);
    void findKeybindsForAction(const std::string& action, const int playerIdx, std::vector<KeyBind>& out);
    bool getKeyPressed(const int keyCode) const;
    void setKeyPressed(const int keyCode, const bool value);

public:
    InputManager(InputManager const& copy) = delete;
    InputManager& operator=(InputManager const& copy) = delete;

    static InputManager& getInstance();

    bool isKeyDown(const int keyCode);
    bool isKeyUp(const int keyCode);
    bool isKeyPressed(const int keyCode);
    bool isKeyReleased(const int keyCode);

    bool isKeyDown(const std::string& action, const int playerIdx);
    bool isKeyUp(const std::string& action, const int playerIdx);
    bool isKeyPressed(const std::string& action, const int playerIdx);
    bool isKeyReleased(const std::string& action, const int playerIdx);

    void bind(const std::string& name, const int keyCode, const int playerIdx);
    void unbind(const std::string& name, const int playerIdx);
    void unbind(const int keyCode, const int playerIdx);
};
