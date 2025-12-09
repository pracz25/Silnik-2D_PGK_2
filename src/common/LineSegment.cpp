#include "LineSegment.hpp"
#include "PrimitiveRenderer.hpp"

LineSegment::LineSegment()
    : m_a(), m_b(), m_color(sf::Color::White), m_renderer(nullptr)
{}

LineSegment::LineSegment(PrimitiveRenderer& renderer,
                         const Point2D& a,
                         const Point2D& b,
                         sf::Color color)
    : m_a(a), m_b(b), m_color(color), m_renderer(&renderer)
{}

void LineSegment::translate(float dx, float dy) {
    m_a.translate(dx, dy);
    m_b.translate(dx, dy);
}

void LineSegment::rotate(float angleDeg) {
    m_a.rotate(angleDeg);
    m_b.rotate(angleDeg);
}

void LineSegment::scale(float sx, float sy) {
    m_a.scale(sx, sy);
    m_b.scale(sx, sy);
}

void LineSegment::draw(sf::RenderTarget& target) {
    if (m_renderer) {
        m_renderer->drawLineIncremental(
            target,
            m_a.position(),
            m_b.position(),
            m_color
        );
    }
    else {
        sf::Vertex v[2] = {
            sf::Vertex(m_a.position(), m_color),
            sf::Vertex(m_b.position(), m_color)
        };
        target.draw(v, 2, sf::Lines);
    }
}
