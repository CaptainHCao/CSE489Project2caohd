#pragma once
#include "LightComponent.h"
#include "SharedLighting.h"

class DirectionalLightComponent :
    public LightComponent
{
public:
    DirectionalLightComponent(int controlKey, int updateOrder = 100);
    virtual void update(const float& deltaTime) override;
};

