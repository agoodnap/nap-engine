#pragma once

#include <memory>
#include <utility>

#include "RenderComponent.h"

class ShapeComponent : public RenderComponent
{
protected:
	std::shared_ptr<sf::Texture> m_texture{};
	bool m_rotateWithParent;
public:
	ShapeComponent(GameObject& parent);
	~ShapeComponent() override;
	void update(const float deltaTime) override = 0;
	virtual void setScale(const float x, const float y) = 0;
	virtual void setSmooth(const bool value) = 0;
	virtual void setTexture(::std::shared_ptr<sf::Texture> texture) { m_texture = std::move(texture); }
	virtual void setFillColor(sf::Color color) = 0;
	virtual void setOutlineColor(sf::Color color) = 0;
	virtual void setOutlineThickness(const float value) = 0;
	virtual void setRotation(const float value) = 0;
	void setRotateWithParent(const bool val) { m_rotateWithParent = val; }
	bool rotatesWithParent() const { return m_rotateWithParent; }
	virtual std::shared_ptr<sf::Texture> getTexture() { return m_texture; };
	virtual void setOrigin(const float x, const float y) = 0;
	virtual std::shared_ptr<sf::Shape> getShape() = 0;
	std::vector<std::weak_ptr<sf::Drawable>> getDrawables() override = 0;
};

