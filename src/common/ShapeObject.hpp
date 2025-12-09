#pragma once
#include "DrawableObject.hpp"
#include "TransformableObject.hpp"

class ShapeObject :
    public virtual DrawableObject,
    public virtual TransformableObject
{
public:
    virtual ~ShapeObject() = default;
};