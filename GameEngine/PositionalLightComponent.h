#pragma once
#include "LightComponent.h"
#include "SharedLighting.h"

class PositionalLightComponent :
    public LightComponent
{
public:
    PositionalLightComponent(int controlKey, int updateOrder = 100);
    virtual void update(const float& deltaTime) override;
};

