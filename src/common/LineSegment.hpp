#pragma once
#include "ShapeObject.hpp"
#include "Point2D.hpp"

class PrimitiveRenderer;

class LineSegment : public ShapeObject {
    Point2D m_a;
    Point2D m_b;
    sf::Color m_color;
    PrimitiveRenderer* m_renderer;

public:
    LineSegment();
    LineSegment(PrimitiveRenderer& renderer,
                const Point2D& a,
                const Point2D& b,
                sf::Color color = sf::Color::White);

    const Point2D& a() const { return m_a; }
    const Point2D& b() const { return m_b; }

    void setRenderer(PrimitiveRenderer& r) { m_renderer = &r; }
    void setColor(const sf::Color& c) { m_color = c; }

    void translate(float dx, float dy) override;
    void rotate(float angleDeg) override;
    void scale(float sx, float sy) override;

    void draw(sf::RenderTarget& target) override;
};
