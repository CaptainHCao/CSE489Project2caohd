#include "SteerComponent.h"

//contructor
SteerComponent::SteerComponent(float turnRate, int updateOrder)
	: Component(updateOrder), turnRate(turnRate)
{}

//Update() check every second for steering movement
void SteerComponent::update(const float& deltaTime)
{
	vec4 fwd = vec4(owningGameObject->getFowardDirection(), 0.0f);

	vec3 newFwd = fwd.xyz;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT)) {
		newFwd = (glm::rotate(glm::radians(-turnRate) * deltaTime, UNIT_Y_V3) * fwd).xyz;

	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT)) {

		newFwd = (glm::rotate(glm::radians(turnRate) * deltaTime, UNIT_Y_V3) * fwd).xyz;

	}

	owningGameObject->rotateTo(newFwd);

}