#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "common/PrimitiveRenderer.hpp"
#include "common/BitmapHandler.hpp"
#include "common/SpriteObject.hpp"
#include "common/Player.hpp"
#include "common/GameObject.hpp"

class Engine {
    sf::RenderWindow m_window;
    PrimitiveRenderer m_renderer;

    std::vector<std::shared_ptr<GameObject>> m_objects;
    std::shared_ptr<Player> m_player;

    sf::Image  m_imgBoundary;
    sf::Texture m_texBoundary;
    sf::Sprite  m_sprBoundary;

    sf::Image  m_imgFlood;
    sf::Texture m_texFlood;
    sf::Sprite  m_sprFlood;

public:
    Engine();
    bool isOpen() const;

    void initPlayer();
    void initFillDemos();

    void handleEvents();
    void handleInput();
    void update(float dt);
    void render();

    void run();
};
