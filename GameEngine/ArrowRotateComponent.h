#pragma once
#include "Component.h"

class ArrowRotateComponent :
    public Component
{
public:
    ArrowRotateComponent(int updateOrder = 100);

    virtual void initialize() override;

    virtual void processInput() override;

    virtual void update(const float& deltaTime) override;

protected:

    float rotationY = 0.0f, rotationX = 0.0f;

    const float ROTATION_INC = glm::radians(20.f);
};

