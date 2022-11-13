#include "SolarTravelComponent.h"
#define VERBOSE false

//constructor 
SolarTravelComponent::SolarTravelComponent(std::vector<GameObject*> planets, vec3 velocity, int updateOrder)
	:Component(updateOrder), velocity(velocity), speed(glm::length(velocity)), planets(planets),
	targetPlanetIndex(static_cast<int>(planets.size()) - 1)
{
	componentType = MOVE;
}

//override update 
void SolarTravelComponent::update(const float& deltaTime)
{
	//range that the spaceship slow down and tag along
	float radius = 4.0;

	//get user's input to determine which planet to go to
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_0)) {
		targetPlanetIndex = 0; //the sun
		isMoving = true;
		StartMoving();
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_1)) {
		targetPlanetIndex = 1; //the earth
		isMoving = true;
		StartMoving();
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_2)) {
		targetPlanetIndex = 2; //the mars
		isMoving = true;
		StartMoving();
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_3)) {
		targetPlanetIndex = 3; //the jupiter
		isMoving = true;
		StartMoving();
	}

	if (isMoving) {
		// Check if next Planet has been reached
		if (distanceToTargetPlanet() < (speed * deltaTime + radius)) {
			if (targetPlanetIndex == 0) 
			{
				Stop();
			}
			else TagAlong();
		}
		else {
			StartMoving();
		}

		if (VERBOSE) cout << speed << " " << endl;

		// Get current facing directions
		vec3 current = owningGameObject->getFowardDirection(WORLD);

		// Get direction to the next Planet
		vec3 desiredDirection = getDirectionToNextPlanet();

		// Incrementally update current direction to face the next Planet
		vec3 newDirection = glm::lerp(current, desiredDirection, deltaTime);

		// Rotate to face the new direction
		owningGameObject->rotateTo(newDirection, WORLD);

		// Get the current position
		vec3 position = owningGameObject->getPosition(WORLD);

		// Update the position based on the newDirection
		position = position + newDirection * speed * deltaTime;

		// Set the position of the GameObject
		owningGameObject->setPosition(position, WORLD);
	}
} // end update


vec3 SolarTravelComponent::getDirectionToNextPlanet()
{
	return glm::normalize((planets[targetPlanetIndex]->getPosition() - owningGameObject->getPosition(WORLD)));
} // end getDirectionToNextPlanet

GLfloat SolarTravelComponent::distanceToTargetPlanet()
{
	GLfloat dist = glm::distance(planets[targetPlanetIndex]->getPosition(), owningGameObject->getPosition(WORLD));

	if (VERBOSE) cout << dist << endl;

	return dist;

}

void SolarTravelComponent::TagAlong()
{
	speed = 5.0f;
}

void SolarTravelComponent::StartMoving()
{
	speed = 6.0f;
}

void SolarTravelComponent::Stop()
{
	speed = 0.0f;
}