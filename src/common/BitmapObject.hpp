#pragma once
#include "DrawableObject.hpp"
#include "TransformableObject.hpp"
#include <SFML/Graphics.hpp>

class BitmapObject :
    public virtual DrawableObject,
    public virtual TransformableObject
{
protected:
    sf::Sprite m_sprite;

public:
    virtual ~BitmapObject() = default;

    void setTexture(const sf::Texture& tex) {
        m_sprite.setTexture(tex);
    }

    void translate(float dx, float dy) override {
        m_sprite.move(dx, dy);
    }

    void rotate(float angleDeg) override {
        m_sprite.rotate(angleDeg);
    }

    void scale(float sx, float sy) override {
        m_sprite.scale(sx, sy);
    }

    void draw(sf::RenderTarget& target) override {
        target.draw(m_sprite);
    }

    sf::Vector2f position() const {
        return m_sprite.getPosition();
    }
};
