#pragma once
#include "DrawableObject.hpp"
#include "UpdatableObject.hpp"

class GameObject :
    public virtual DrawableObject,
    public virtual UpdatableObject
{
public:
    virtual ~GameObject() = default;
};
