#pragma once

class TransformableObject {
public:
    virtual ~TransformableObject() = default;

    virtual void translate(float dx, float dy) = 0;
    virtual void rotate(float angleDeg) = 0;
    virtual void scale(float sx, float sy) = 0;
};
