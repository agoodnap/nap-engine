#pragma once

#include <memory>
#include <vector>

#include "RenderComponent.h"

class SpriteComponent : public RenderComponent
{
private:
	std::shared_ptr<sf::Texture> m_texture{};
	std::shared_ptr<sf::Sprite> m_sprite{};
	bool m_rotateWithParent;
public:
	SpriteComponent(GameObject& parent);
	~SpriteComponent() override;
	void update(const float deltaTime) override;
	void setScale(const float x, const float y);
	void setSmooth(const bool value);
	void setTexture(std::shared_ptr<sf::Texture> texture);
	void setColor(sf::Color color);
	std::shared_ptr<sf::Texture> getTexture();
	void setOrigin(const float x, const float y);
	sf::Vector2f getOrigin();
	std::shared_ptr<sf::Sprite> getSprite();

	void setRotateWithParent(const bool val);
	bool rotatesWithParent() const;

	virtual std::vector<std::weak_ptr<sf::Drawable>> getDrawables() override;
};

