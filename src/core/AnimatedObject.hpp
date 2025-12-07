#pragma once

class AnimatedObject {
public:
    virtual ~AnimatedObject() = default;
    virtual void animate(float dt) = 0;
};
