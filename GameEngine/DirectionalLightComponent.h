#pragma once
#include "LightComponent.h"
#include "SharedLighting.h"

class DirectionalLightComponent :
    public LightComponent
{
    virtual void update(const float& deltaTime) override;
};

