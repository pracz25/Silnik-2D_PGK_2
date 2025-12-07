#pragma once
#include "UpdatableObject.hpp"
#include "DrawableObject.hpp"

class GameObject : public virtual UpdatableObject,
                   public virtual DrawableObject {
public:
    virtual ~GameObject() = default;
};
