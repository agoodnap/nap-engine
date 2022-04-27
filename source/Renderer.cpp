#include "Renderer.h"

#include <algorithm>

#include "RenderComponent.h"
#include "GameObject.h"

Renderer& Renderer::getInstance()
{
    static Renderer instance;
    return instance;
}

Renderer::Renderer() : m_currentCam(), m_renderObjects()
{
}

Renderer::~Renderer()
{
    m_renderObjects.clear();
}

bool Renderer::initWindow(unsigned const int windowX, unsigned const int windowY, const std::string& title)
{
    m_window.create(sf::VideoMode(windowX, windowY), title);
    return true;
}

sf::RenderWindow& Renderer::getWindow()
{
    return m_window;
}

bool Renderer::isWindowOpen() const
{
    return m_window.isOpen();
}

bool Renderer::pollEvent(sf::Event& event)
{
    if (!m_window.isOpen())
    {
        return false;
    }

    const auto result = m_window.pollEvent(event);
    
    return result;
}

void Renderer::closeWindow()
{
    if (m_window.isOpen())
    {
        m_window.close();
    }
}

void Renderer::clear()
{
    m_window.clear();
}

void Renderer::setWindowSize(unsigned const int windowX, unsigned const int windowY)
{
    sf::Vector2u newSize;
    newSize.x = windowX;
    newSize.y = windowY;
    m_window.setSize(newSize);
}

void Renderer::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
    if (m_window.isOpen())
    {
        m_window.draw(drawable, states);
    }
}

bool orderSort(const std::weak_ptr<RenderComponent>& a, const std::weak_ptr<RenderComponent>& b)
{
    if (a.expired() || b.expired())
    {
        return false;
    }

    const auto aComp = a.lock();
    const auto bComp = b.lock();
    if (aComp && bComp)
    {
        return aComp->getRenderOrder() < bComp->getRenderOrder();
    }

    return false;
}

void Renderer::display()
{
    if (const auto cam = m_currentCam.lock())
    {
        m_window.setView(cam->getView());
    }

    std::sort(m_renderObjects.begin(), m_renderObjects.end(), orderSort);

    for (auto obj = m_renderObjects.begin(); obj != m_renderObjects.end();)
    {
        if (const auto renderComp = obj->lock())
        {
            if (renderComp->getParent().isEnabled())
            {
                auto drawables = renderComp->getDrawables();
                for (const auto& drawable : drawables)
                {
                    if (auto drawWeakPtr = drawable.lock())
                    {
                        draw(*drawWeakPtr);
                    }
                }
            }
            ++obj;
        }
        else
        {
            obj = m_renderObjects.erase(obj);
        }
    }

    m_window.display();
}

sf::Vector2f Renderer::getCenter() const
{
    if (const auto cam = m_currentCam.lock())
    {
        return cam->getView().getCenter();
    }

    return m_window.getView().getCenter();
}

void Renderer::setCamera(const std::shared_ptr<CameraComponent>& camera)
{
    m_currentCam = std::weak_ptr<CameraComponent>(camera);
}

void Renderer::registerRenderComponent(const std::shared_ptr<RenderComponent>& component)
{
    const std::weak_ptr<RenderComponent> toInsert = component;
    m_renderObjects.push_back(toInsert);
    std::sort(m_renderObjects.begin(), m_renderObjects.end(), orderSort);
}

void Renderer::cullExpiredComponents()
{
    for (auto obj = m_renderObjects.begin(); obj != m_renderObjects.end();)
    {
        const auto renderComp = obj->lock();
        if (!renderComp)
        {
            obj = m_renderObjects.erase(obj);
        }
        else
        {
            ++obj;
        }
    }
}

void Renderer::reorderRenderComponents()
{
    std::sort(m_renderObjects.begin(), m_renderObjects.end(), orderSort);
}
