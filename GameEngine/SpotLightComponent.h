#pragma once
#include "LightComponent.h"
#include "SharedLighting.h"

class SpotLightComponent :
    public LightComponent
{
    public: 
        SpotLightComponent(int controlKey, int updateOrder = 100);
        virtual void update(const float& deltaTime) override;
};

