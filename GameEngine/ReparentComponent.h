#pragma once
#include "Component.h"
class ReparentComponent :
    public Component
{
public:
    ReparentComponent(GameObject* newParent, float radius, int updateOrder = 100);

    virtual void update(const float& deltaTime) override;

protected:
    GameObject* newParent;
    float radius;

    GLfloat distanceToNewParent();

    GLvoid reparent();
};

