#pragma once
#include "Component.h"
class WaypointComponent : public Component
{
public:
    WaypointComponent(std::vector<vec3> waypoints, float speed = 10.0f, int updateOrder = 100);

    // Positions the object at the first waypoint
    virtual void initialize() override;

    // Causes the game object to loop through a series of positions repeatedly
    virtual void update(const float& deltaTime) override;

protected:

    std::vector<vec3> waypoints;

    float speed = 10.0f;

};


