#pragma once
#include "Component.h"
class TranslateComponent :  public Component
{
public:
    TranslateComponent(vec3 velocity, int updateOrder = 100);

    virtual void initialize() override;


    virtual void update(const float& deltaTime) override;

protected:

    vec3 velocity = ZERO_V3;

};

