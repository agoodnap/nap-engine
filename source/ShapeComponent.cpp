#include "ShapeComponent.h"
#include "GameObject.h"

ShapeComponent::ShapeComponent(GameObject& parent) : RenderComponent(parent), m_texture(nullptr),
                                                     m_rotateWithParent(true)
{
}

ShapeComponent::~ShapeComponent()
= default;
