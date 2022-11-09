#pragma once
#include "Component.h"
class SpinComponent :
    public Component
{
    SpinComponent(vec3 axis, vec3 velocity = vec3(10, 0, 0));

    virtual void update(const float& deltaTime) override;
};

