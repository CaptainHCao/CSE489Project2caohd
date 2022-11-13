#pragma once

#include "Component.h"

class SolarTravelComponent : public Component
{
public:

	//Constructor
	SolarTravelComponent(std::vector<GameObject*> planets, vec3 velocity = vec3(10, 0, 0), int updateOrder = 100);

	//override update
	virtual void update(const float& deltaTime) override;

protected:
	//return direcetion to next planet
	vec3 getDirectionToNextPlanet();

	//return distance to target planet
	GLfloat distanceToTargetPlanet();

	//move along the planet
	void TagAlong();
	//initialize speed 
	void StartMoving();
	//stop moving
	void Stop();

	//objects vector storing planet objects
	std::vector<GameObject*> planets;

	vec3 velocity;

	float speed;

	int targetPlanetIndex = 0;

	bool isMoving = false;
};


