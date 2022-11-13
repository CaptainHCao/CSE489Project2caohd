#include "TranslateComponent.h"

TranslateComponent::TranslateComponent(vec3 velocity, int updateOrder)
	: Component(updateOrder), velocity(velocity)
{
	componentType = MOVE;
}

void TranslateComponent::initialize()
{
	cout << " ArrowRotateComponent::initialize" << endl;

	owningGameObject->setPosition(vec3(0.0f, 0.0f, -5.0f));
}


// reduced update() 
void TranslateComponent::update(const float& deltaTime)
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP))
	{
		vec4 fwd = vec4(owningGameObject->getFowardDirection(), 0.0f);

		vec3 newFwd = fwd.xyz;

		vec3 position = owningGameObject->getPosition();

		position += glm::length(velocity) * newFwd * deltaTime;

		owningGameObject->setPosition(position);
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN))
	{
		vec4 fwd = vec4(owningGameObject->getFowardDirection(), 0.0f);

		vec3 newFwd = fwd.xyz;

		vec3 position = owningGameObject->getPosition();

		position -= glm::length(velocity) * newFwd * deltaTime;

		owningGameObject->setPosition(position);
	}
}
