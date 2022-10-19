#pragma once
#include "Component.h"

class ContinuousRotateComponent : public Component
{
public:
    ContinuousRotateComponent(float rotationRate, vec3 axis, int updateOrder = 150);

    virtual void update(const float& deltaTime) override;

protected:

    // Axis of rotation
    vec3 axis = UNIT_Y_V3;

    // Rotation rate in radians per second
    float rotationRate;

};



