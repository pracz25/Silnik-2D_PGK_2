#include "Engine.hpp"
#include "common/PrimitiveRenderer.hpp"

Engine::Engine()
    : m_window(sf::VideoMode(1000, 700), "Silnik 2D - demo PGK")
{
    m_window.setFramerateLimit(60);

    initPlayer();
    initFillDemos();
}

bool Engine::isOpen() const { return m_window.isOpen(); }

void Engine::initPlayer()
{
    const unsigned W = 32, H = 48;
    std::vector<sf::Texture> frames;

    for (int i = 0; i < 4; ++i) {
        sf::Image img;
        img.create(W, H, sf::Color(100 + 30 * i, 100 + 20 * i, 255 - 30 * i));

        for (unsigned x = 0; x < W; ++x) {
            img.setPixel(x, 0, sf::Color::Black);
            img.setPixel(x, H - 1, sf::Color::Black);
        }
        for (unsigned y = 0; y < H; ++y) {
            img.setPixel(0, y, sf::Color::Black);
            img.setPixel(W - 1, y, sf::Color::Black);
        }

        sf::Texture tex;
        tex.loadFromImage(img);
        frames.push_back(tex);
    }

    m_player = std::make_shared<Player>();
    m_player->setFrames(frames);
    m_player->setTimePerFrame(0.2f);
    m_player->translate(200.f, 400.f);

    m_objects.push_back(m_player);
}

void Engine::initFillDemos()
{
    m_imgBoundary.create(200, 150, sf::Color::White);
    sf::Color border = sf::Color::Black;

    for (unsigned x = 10; x < 190; ++x) {
        m_imgBoundary.setPixel(x, 10, border);
        m_imgBoundary.setPixel(x, 140, border);
    }
    for (unsigned y = 10; y < 140; ++y) {
        m_imgBoundary.setPixel(10, y, border);
        m_imgBoundary.setPixel(190, y, border);
    }

    m_renderer.boundaryFill(m_imgBoundary, 50, 50,
                            sf::Color(200, 255, 200),
                            border);

    m_texBoundary.loadFromImage(m_imgBoundary);
    m_sprBoundary.setTexture(m_texBoundary);
    m_sprBoundary.setPosition(700.f, 50.f);

    m_imgFlood.create(200, 150, sf::Color(240, 240, 255));

    for (unsigned x = 0; x < 200; ++x) {
        m_imgFlood.setPixel(x, 0, sf::Color::Black);
        m_imgFlood.setPixel(x, 149, sf::Color::Black);
    }
    for (unsigned y = 0; y < 150; ++y) {
        m_imgFlood.setPixel(0, y, sf::Color::Black);
        m_imgFlood.setPixel(199, y, sf::Color::Black);
    }

    m_renderer.floodFill(m_imgFlood, 100, 75,
                         sf::Color(255, 220, 200));

    m_texFlood.loadFromImage(m_imgFlood);
    m_sprFlood.setTexture(m_texFlood);
    m_sprFlood.setPosition(700.f, 250.f);
}

void Engine::handleEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            m_window.close();
    }
}

void Engine::handleInput()
{
    sf::Vector2f vel(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) vel.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) vel.x += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) vel.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) vel.y += 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) m_player->rotate(-1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) m_player->rotate(1.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) m_player->scale(1.001f, 1.001f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) m_player->scale(0.999f, 0.999f);

    float speed = 150.f;
    m_player->setVelocity(vel * speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        m_window.close();
}

void Engine::update(float dt)
{
    for (auto& o : m_objects)
        o->update(dt);
}

void Engine::render()
{
    m_window.clear(sf::Color(220, 220, 220));

    m_renderer.drawLineDefault(m_window, {50, 50}, {300, 100}, sf::Color::Red);
    m_renderer.drawLineIncremental(m_window, {50, 100}, {300, 200}, sf::Color::Blue);

    m_renderer.drawCircle(m_window, {200, 300}, 60, sf::Color::Black);
    m_renderer.drawEllipse(m_window, {400, 300}, 80, 40, sf::Color::Black);

    std::vector<sf::Vector2f> poly = {
        {100, 400}, {200, 450}, {180, 550}, {60, 520}
    };
    m_renderer.drawPolygon(m_window, poly, sf::Color::Magenta);

    m_window.draw(m_sprBoundary);
    m_window.draw(m_sprFlood);

    for (auto& o : m_objects)
        o->draw(m_window);

    m_window.display();
}

void Engine::run()
{
    sf::Clock clock;
    while (m_window.isOpen()) {
        float dt = clock.restart().asSeconds();
        handleEvents();
        handleInput();
        update(dt);
        render();
    }
}
