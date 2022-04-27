#pragma once

#include <memory>
#include <string>
#include <vector>

#include "CameraComponent.h"

class RenderComponent;

class Renderer
{
private:
    sf::RenderWindow m_window{};
    std::weak_ptr<CameraComponent> m_currentCam;
    std::vector<std::weak_ptr<RenderComponent>> m_renderObjects;

    ~Renderer();
    Renderer();
    void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

public:
    Renderer(Renderer const& copy) = delete;
    Renderer& operator=(Renderer const& copy) = delete;

    static Renderer& getInstance();

    bool initWindow(unsigned const int windowX, unsigned const int windowY, const std::string& title);
    sf::RenderWindow& getWindow();
    bool isWindowOpen();
    bool pollEvent(sf::Event& event);
    void closeWindow();
    void setWindowSize(unsigned const int windowX, unsigned const int windowY);
    void clear();
    void display();
    sf::Vector2f getCenter() const;
    void setCamera(std::shared_ptr<CameraComponent> camera);
    void registerRenderComponent(std::shared_ptr<RenderComponent> component);
    void cullExpiredComponents();
    void reorderRenderComponents();
};
