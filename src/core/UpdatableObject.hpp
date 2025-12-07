#pragma once

class UpdatableObject {
public:
    virtual ~UpdatableObject() = default;
    virtual void update(float dt) = 0;
};
