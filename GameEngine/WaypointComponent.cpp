#include "WaypointComponent.h"
#define VERBOSE false

//initialized the position to the first waypoint
WaypointComponent::WaypointComponent(std::vector< glm::vec3> waypoints, vec3 velocity)
	: velocity(velocity), speed(glm::length(velocity)), waypoints(waypoints),
	targetWaypointIndex(static_cast<int>(waypoints.size()) - 1)
{
	targetWaypointIndex = getNexWaypointIndex();
	componentType = MOVE;
}

int index; //index of current destination waypoint

void WaypointComponent::update(const float& deltaTime)
{
	float radius = 1.0;

	// Check if next waypoint has been reached
	if (distanceToTargetWaypoint() < (speed * deltaTime + radius)) {
		targetWaypointIndex = getNexWaypointIndex();
	}

	// Get current facing directions
	vec3 current = owningGameObject->getFowardDirection(WORLD);

	// Get direction to the next waypoint
	vec3 desiredDirection = getDirectionToNextWaypoint();

	// Incrementally update current direction to face the next waypoint
	vec3 newDirection = glm::lerp(current, desiredDirection, deltaTime);

	// Rotate to face the new direction
	owningGameObject->rotateTo(newDirection, WORLD);

	// Get the current position
	vec3 position = owningGameObject->getPosition(WORLD);

	// Update the position based on the newDirection
	position = position + newDirection * speed * deltaTime;

	// Set the position of the GameObject
	owningGameObject->setPosition(position, WORLD);

} // end update


int WaypointComponent::getNexWaypointIndex()
{
	return (targetWaypointIndex + 1) % waypoints.size();

} // end getNexWaypointIndex

vec3 WaypointComponent::getDirectionToNextWaypoint()
{
	return glm::normalize((waypoints[targetWaypointIndex] - owningGameObject->getPosition(WORLD)));

} // end getDirectionToNextWaypoint

GLfloat WaypointComponent::distanceToTargetWaypoint()
{
	GLfloat dist = glm::distance(waypoints[targetWaypointIndex], owningGameObject->getPosition(WORLD));

	if (VERBOSE) cout << dist << endl;

	return dist;

}

