#pragma once
#include "LightComponent.h"
#include "SharedLighting.h"

class SpotLightComponent :
    public LightComponent
{
    virtual void update(const float& deltaTime) override;
};

