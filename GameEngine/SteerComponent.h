#pragma once
#include "Component.h"

class SteerComponent : public Component
{
public:
    SteerComponent(float turnRate, int updateOrder = 100);

    virtual void update(const float& deltaTime) override;

protected:

    // Turn rate in radians per second
    float turnRate;

};


