#pragma once
#include "Component.h"

class ReparentComponent :
    public Component
{
public:
    //constructor
    ReparentComponent(GameObject* newParent, float radius, int updateOrder = 100);

    //override update
    virtual void update(const float& deltaTime) override;

protected:
    //new object to be reparent to 
    GameObject* newParent;

    //the radius that the child game object will be reparented
    float radius;

    //find the distance to the potential new parent game object
    GLfloat distanceToNewParent();

    //carry out the reparenting process
    GLvoid reparent();
};

