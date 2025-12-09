#pragma once
#include "SpriteObject.hpp"
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class Player :
    public SpriteObject,
    public GameObject
{
    sf::Vector2f m_velocity {0.f, 0.f};
    float m_speed {150.f};

public:
    Player() = default;

    void setVelocity(const sf::Vector2f& v) {
        m_velocity = v;
    }

    void update(float dt) override {
        m_sprite.move(m_velocity * dt);
        SpriteObject::update(dt);
    }
};
