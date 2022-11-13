#include "ContinuousRotateComponent.h"

ContinuousRotateComponent::ContinuousRotateComponent(float rotationRate, vec3 axis, int updateOrder)
	: Component(updateOrder), rotationRate(rotationRate), axis(axis)
{
	componentType = MOVE;
}

//Passively rotate every update
void ContinuousRotateComponent::update(const float& deltaTime)
{
	mat4 rot = owningGameObject->getRotation(LOCAL);
	rot *= glm::rotate(glm::radians(rotationRate) * deltaTime, axis);
	this->owningGameObject->setRotation(rot, LOCAL);
}