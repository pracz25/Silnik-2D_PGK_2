#pragma once
#include <SFML/Graphics.hpp>

class BitmapHandler {
public:
    static sf::Image create(unsigned width, unsigned height,
                            sf::Color color = sf::Color::Transparent)
    {
        sf::Image img;
        img.create(width, height, color);
        return img;
    }

    static bool loadFromFile(const std::string& filename, sf::Image& img) {
        return img.loadFromFile(filename);
    }

    static bool saveToFile(const std::string& filename, const sf::Image& img) {
        return img.saveToFile(filename);
    }

    static void copy(const sf::Image& src, sf::Image& dst,
                     sf::Vector2u dstPos = {0, 0})
    {
        dst.copy(src, dstPos.x, dstPos.y, sf::IntRect(), true);
    }
};
