#pragma once
#include "BitmapObject.hpp"
#include "AnimatedObject.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class SpriteObject :
    public BitmapObject,
    public AnimatedObject
{
protected:
    std::vector<sf::Texture> m_frames;
    float m_timePerFrame {0.15f};
    float m_timeAccumulator {0.f};
    std::size_t m_currentFrame {0};

public:
    virtual ~SpriteObject() = default;

    void setFrames(const std::vector<sf::Texture>& frames) {
        m_frames = frames;
        if (!m_frames.empty()) {
            m_currentFrame = 0;
            m_sprite.setTexture(m_frames[0], true);
        }
    }

    void setTimePerFrame(float t) { m_timePerFrame = t; }

    void animate(float dt) override {
        if (m_frames.empty()) return;

        m_timeAccumulator += dt;
        if (m_timeAccumulator >= m_timePerFrame) {
            m_timeAccumulator -= m_timePerFrame;
            m_currentFrame = (m_currentFrame + 1) % m_frames.size();
            m_sprite.setTexture(m_frames[m_currentFrame], true);
        }
    }

    void update(float dt) override {
        animate(dt);
    }
};
