#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <cmath>

class PrimitiveRenderer {

    static void putPixel(sf::RenderTarget& target, int x, int y, sf::Color color) {
        sf::Vertex v(sf::Vector2f((float)x, (float)y), color);
        target.draw(&v, 1, sf::Points);
    }

public:
    PrimitiveRenderer() = default;

    void drawLineDefault(sf::RenderTarget& target,
                         const sf::Vector2f& a,
                         const sf::Vector2f& b,
                         sf::Color color)
    {
        sf::Vertex verts[2] = { sf::Vertex(a, color), sf::Vertex(b, color) };
        target.draw(verts, 2, sf::Lines);
    }

    void drawLineIncremental(sf::RenderTarget& target,
                             const sf::Vector2f& a,
                             const sf::Vector2f& b,
                             sf::Color color)
    {
        float x0 = a.x, y0 = a.y;
        float x1 = b.x, y1 = b.y;
        float dx = x1 - x0;
        float dy = y1 - y0;

        if (dx == 0 && dy == 0) {
            putPixel(target, (int)round(x0), (int)round(y0), color);
            return;
        }

        bool steep = fabs(dy) > fabs(dx);
        if (steep) {
            std::swap(x0, y0);
            std::swap(x1, y1);
            std::swap(dx, dy);
        }

        if (x0 > x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
            dx = x1 - x0;
            dy = y1 - y0;
        }

        float m = dx == 0 ? 0 : dy / dx;
        float y = y0;

        for (int x = (int)round(x0); x <= (int)round(x1); ++x) {
            int px = steep ? (int)round(y) : x;
            int py = steep ? x : (int)round(y);
            putPixel(target, px, py, color);
            y += m;
        }
    }

    void drawCircle(sf::RenderTarget& target,
                    const sf::Vector2f& center,
                    float R,
                    sf::Color color,
                    unsigned steps = 64)
    {
        const float pi = 3.14159265359f;
        float x0 = center.x, y0 = center.y;

        for (unsigned i = 0; i <= steps; ++i) {
            float alpha = (pi / 4.f) * i / steps;
            float x = R * cos(alpha);
            float y = R * sin(alpha);

            int px[8] = {
                (int)round(x0 + x), (int)round(x0 + y),
                (int)round(x0 - x), (int)round(x0 - y),
                (int)round(x0 - x), (int)round(x0 - y),
                (int)round(x0 + x), (int)round(x0 + y)
            };
            int py[8] = {
                (int)round(y0 + y), (int)round(y0 + x),
                (int)round(y0 + y), (int)round(y0 + x),
                (int)round(y0 - y), (int)round(y0 - x),
                (int)round(y0 - y), (int)round(y0 - x)
            };

            for (int k = 0; k < 8; k++)
                putPixel(target, px[k], py[k], color);
        }
    }

    void drawEllipse(sf::RenderTarget& target,
                     const sf::Vector2f& center,
                     float Rx, float Ry,
                     sf::Color color,
                     unsigned steps = 90)
    {
        const float pi = 3.14159265359f;
        float x0 = center.x, y0 = center.y;

        for (unsigned i = 0; i <= steps; ++i) {
            float alpha = (pi / 2.f) * i / steps;
            float x = Rx * cos(alpha);
            float y = Ry * sin(alpha);

            int px[4] = {(int)round(x0 + x),(int)round(x0 - x),
                         (int)round(x0 + x),(int)round(x0 - x)};
            int py[4] = {(int)round(y0 + y),(int)round(y0 + y),
                         (int)round(y0 - y),(int)round(y0 - y)};

            for (int k = 0; k < 4; k++)
                putPixel(target, px[k], py[k], color);
        }
    }

    static float cross(const sf::Vector2f& a,
                       const sf::Vector2f& b,
                       const sf::Vector2f& c)
    {
        return (b.x - a.x) * (c.y - a.y)
             - (b.y - a.y) * (c.x - a.x);
    }

    static bool segmentsIntersect(const sf::Vector2f& a1, const sf::Vector2f& a2,
                                  const sf::Vector2f& b1, const sf::Vector2f& b2)
    {
        float d1 = cross(a1, a2, b1);
        float d2 = cross(a1, a2, b2);
        float d3 = cross(b1, b2, a1);
        float d4 = cross(b1, b2, a2);

        return (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
                ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)));
    }

    bool drawPolygon(sf::RenderTarget& target,
                     const std::vector<sf::Vector2f>& pts,
                     sf::Color color)
    {
        if (pts.size() < 3) return false;

        size_t n = pts.size();

        for (size_t i = 0; i < n; ++i) {
            sf::Vector2f a1 = pts[i];
            sf::Vector2f a2 = pts[(i + 1) % n];

            for (size_t j = i + 1; j < n; ++j) {
                if (j == i) continue;
                if ((j + 1) % n == i || (i + 1) % n == j) continue;

                sf::Vector2f b1 = pts[j];
                sf::Vector2f b2 = pts[(j + 1) % n];

                if (segmentsIntersect(a1, a2, b1, b2))
                    return false;
            }
        }

        for (size_t i = 0; i < n; ++i) {
            drawLineIncremental(
                target,
                pts[i],
                pts[(i + 1) % n],
                color
            );
        }
        return true;
    }

    void boundaryFill(sf::Image& img,
                      int x, int y,
                      const sf::Color& fillColor,
                      const sf::Color& boundaryColor)
    {
        auto size = img.getSize();
        if (x < 0 || y < 0 || x >= (int)size.x || y >= (int)size.y) return;

        sf::Color start = img.getPixel(x, y);
        if (start == boundaryColor || start == fillColor) return;

        std::queue<sf::Vector2i> q;
        q.push({x, y});

        while (!q.empty()) {
            auto p = q.front(); q.pop();

            if (p.x < 0 || p.y < 0 ||
                p.x >= (int)size.x || p.y >= (int)size.y)
                continue;

            auto c = img.getPixel(p.x, p.y);
            if (c == boundaryColor || c == fillColor)
                continue;

            img.setPixel(p.x, p.y, fillColor);

            q.push({p.x + 1, p.y});
            q.push({p.x - 1, p.y});
            q.push({p.x, p.y + 1});
            q.push({p.x, p.y - 1});
        }
    }

    void floodFill(sf::Image& img,
                   int x, int y,
                   const sf::Color& fillColor)
    {
        auto size = img.getSize();
        if (x < 0 || y < 0 || x >= (int)size.x || y >= (int)size.y) return;

        sf::Color backgroundColor = img.getPixel(x, y);
        if (backgroundColor == fillColor) return;

        std::queue<sf::Vector2i> q;
        q.push({x, y});

        while (!q.empty()) {
            auto p = q.front(); q.pop();

            if (p.x < 0 || p.y < 0 ||
                p.x >= (int)size.x || p.y >= (int)size.y)
                continue;

            auto c = img.getPixel(p.x, p.y);
            if (c != backgroundColor || c == fillColor)
                continue;

            img.setPixel(p.x, p.y, fillColor);

            q.push({p.x + 1, p.y});
            q.push({p.x - 1, p.y});
            q.push({p.x, p.y + 1});
            q.push({p.x, p.y - 1});
        }
    }
};
