#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "RenderComponent.h"


class GameObject;

class LayerComponent : public RenderComponent
{
private:
    std::vector<std::shared_ptr<sf::Sprite>> m_sprites{};
    int m_width;
    int m_height;
public:
    LayerComponent(GameObject& parent);
    ~LayerComponent() override;
    void update(float deltaTime) override;
    void add(const std::shared_ptr<sf::Sprite>& sprite);
    int getWidth() const;
    void setWidth(const int& width);
    int getHeight() const;
    void setHeight(const int& height);
    virtual std::vector<std::weak_ptr<sf::Drawable>> getDrawables() override;
};
