#pragma once

class AnimatedObject {
public:
    virtual ~AnimatedObject() = default;
    virtual void animate(float dt) = 0;
    virtual void update(float dt) {
        animate(dt);
    }
};
