#pragma once
#include "LightComponent.h"
#include "SharedLighting.h"

class PositionalLightComponent :
    public LightComponent
{
public:
    
    virtual void update(const float& deltaTime) override;
};

