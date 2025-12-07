#pragma once
#include <SFML/Graphics.hpp>

class DrawableObject {
public:
    virtual ~DrawableObject() = default;
    virtual void draw(sf::RenderTarget& target) = 0;
};
