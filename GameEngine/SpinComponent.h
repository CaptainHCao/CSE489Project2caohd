#pragma once
#include "Component.h"
class SpinComponent :
    public Component
{
public:
    SpinComponent(float rotationRate = 10.0f, vec3 axis = UNIT_Y_V3, int updateOrder = 100);

    virtual void update(const float& deltaTime) override;

protected:
    vec3 axis;

    float rotationRate;
};

