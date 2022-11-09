#include "SpinComponent.h"

SpinComponent::SpinComponent(float rotationRate, vec3 axis, int updateOrder) : Component(updateOrder), rotationRate(glm::radians(rotationRate)), axis(axis) 
{

}


void SpinComponent::update(const float& deltaTime) 
{
    mat4 rot = owningGameObject->getRotation(LOCAL);

    rot *= glm::rotate(rotationRate * deltaTime, axis);

    owningGameObject->setRotation(rot, LOCAL);
}
