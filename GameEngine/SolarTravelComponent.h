#pragma once

#include "Component.h"

class SolarTravelComponent : public Component
{
public:

	/**
	 * @fn	WaypointComponent::WaypointComponent(std::vector< glm::vec3> waypoints, vec3 velocity = vec3(10, 0, 0));
	 *
	 * @brief	Constructor
	 *
	 * @param	waypoints	The waypoints.
	 * @param	velocity 	(Optional) The velocity.
	 */
	SolarTravelComponent(std::vector<GameObject*> planets, vec3 velocity = vec3(10, 0, 0));

	virtual void update(const float& deltaTime) override;

protected:

	//int getNextPlanetIndex();
	vec3 getDirectionToNextPlanet();
	GLfloat distanceToTargetPlanet();
	void TagAlong();
	void StartMoving();
	void Stop();

	std::vector<GameObject*> planets;

	vec3 velocity;
	float speed;

	int targetPlanetIndex = 0;

	bool isMoving;
};


