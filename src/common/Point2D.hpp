#pragma once
#include "ShapeObject.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class Point2D : public ShapeObject {
    sf::Vector2f m_pos;
    sf::Color    m_color;

public:
    Point2D() : m_pos(0.f, 0.f), m_color(sf::Color::White) {}

    Point2D(float x, float y, sf::Color color = sf::Color::White)
        : m_pos(x, y), m_color(color) {}

    float x() const { return m_pos.x; }
    float y() const { return m_pos.y; }

    const sf::Vector2f& position() const { return m_pos; }

    void set(float x, float y) { m_pos = {x, y}; }

    void setColor(const sf::Color& c) { m_color = c; }
    sf::Color color() const { return m_color; }

    void translate(float dx, float dy) override {
        m_pos.x += dx;
        m_pos.y += dy;
    }

    void rotate(float angleDeg) override {
        float rad = angleDeg * 3.14159265359f / 180.f;
        float cs = std::cos(rad);
        float sn = std::sin(rad);

        float nx = m_pos.x * cs - m_pos.y * sn;
        float ny = m_pos.x * sn + m_pos.y * cs;

        m_pos = {nx, ny};
    }

    void scale(float sx, float sy) override {
        m_pos.x *= sx;
        m_pos.y *= sy;
    }

    void draw(sf::RenderTarget& target) override {
        sf::Vertex v(m_pos, m_color);
        target.draw(&v, 1, sf::Points);
    }
};
