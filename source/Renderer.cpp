#include "Renderer.h"

#include <algorithm>

#include "RenderComponent.h"
#include "GameObject.h"

using namespace sf;

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
    m_window.create(VideoMode(windowX, windowY), title);
    return true;
}

RenderWindow& Renderer::getWindow()
{
    return m_window;
}

bool Renderer::isWindowOpen()
{
    return m_window.isOpen();
}

bool Renderer::pollEvent(sf::Event& event)
{
    if (!m_window.isOpen())
    {
        return false;
    }

    auto result = m_window.pollEvent(event);
    
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
    Vector2u newSize;
    newSize.x = windowX;
    newSize.y = windowY;
    m_window.setSize(newSize);
}

void Renderer::draw(const Drawable& drawable, const RenderStates& states)
{
    if (m_window.isOpen())
    {
        m_window.draw(drawable, states);
    }
}

bool orderSort(std::weak_ptr<RenderComponent> a, std::weak_ptr<RenderComponent> b)
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
        if (auto renderComp = obj->lock())
        {
            if (renderComp->getParent().isEnabled())
            {
                auto drawables = renderComp->getDrawables();
                for (auto drawable : drawables)
                {
                    if (auto drawWeakPtr = drawable.lock())
                    {
                        draw(*drawWeakPtr.get());
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

void Renderer::setCamera(std::shared_ptr<CameraComponent> camera)
{
    m_currentCam = std::weak_ptr<CameraComponent>(camera);
}

void Renderer::registerRenderComponent(std::shared_ptr<RenderComponent> component)
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
