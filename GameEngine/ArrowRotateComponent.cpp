#include "ArrowRotateComponent.h"

ArrowRotateComponent::ArrowRotateComponent(int updateOrder)
	: Component(updateOrder)
{
	componentType = MOVE;
}

void ArrowRotateComponent::initialize()
{
	cout << " ArrowRotateComponent::initialize" << endl;

}

void ArrowRotateComponent::processInput()
{




}


void ArrowRotateComponent::update(const float& deltaTime)
{
	mat4 rot = owningGameObject->getRotation();

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_J)) {

		rot *= glm::rotate(ROTATION_INC * deltaTime, UNIT_Y_V3);
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_L)) {

		rot *= glm::rotate(-ROTATION_INC * deltaTime, UNIT_Y_V3);

	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_K)) {

		rot *= glm::rotate(-ROTATION_INC * deltaTime, UNIT_X_V3);

	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_I)) {

		rot *= glm::rotate(ROTATION_INC * deltaTime, UNIT_X_V3);

	}
	this->owningGameObject->setRotation(rot);



	//if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT)) {

	//	rotationY += ROTATION_INC * deltaTime;
	//}
	//else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT)) {

	//	rotationY -= ROTATION_INC * deltaTime;
	//}

	//if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP)) {

	//	rotationX -= ROTATION_INC * deltaTime;
	//}
	//else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN)) {

	//	rotationX += ROTATION_INC * deltaTime;

	//}
	//this->owningGameObject->
	//	setRotation(glm::rotate(rotationY, UNIT_Y_V3) * glm::rotate(rotationX, UNIT_X_V3));

}

