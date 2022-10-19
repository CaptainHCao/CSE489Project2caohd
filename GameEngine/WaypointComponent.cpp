#include "WaypointComponent.h"

WaypointComponent::WaypointComponent(std::vector<vec3> waypoints, float speed, int updateOrder)
	: Component(updateOrder), waypoints(waypoints) {}

//initialized the position to the first waypoint
void WaypointComponent::initialize()
{
	owningGameObject->setPosition(waypoints[0]);
}

int index; //index of current destination waypoint

void WaypointComponent::update(const float& deltaTime)
{
	//repeat from the first waypoint
	if (index == waypoints.size()) {
		index = 0;
	}
	//initialize the destination waypoint direction vector and get the object's position
	vec3 destination = waypoints[index];
	vec3 position = owningGameObject->getPosition();

	//increment when close enough
	if (length(destination - position) < speed * deltaTime) {
		index++;
	}
	else {
		//direct object to the destination waypoint
		vec3 towardsDestination = glm::normalize(destination - position);

		vec3 velocity = glm::lerp(velocity, towardsDestination, deltaTime);

		owningGameObject->rotateTo(velocity);
		velocity = speed * normalize(velocity);
		position += velocity * deltaTime;
		owningGameObject->setPosition(position);
	}

}

