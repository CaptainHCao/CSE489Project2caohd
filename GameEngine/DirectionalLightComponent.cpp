#include "DirectionalLightComponent.h"

DirectionalLightComponent::DirectionalLightComponent(int controlKey, int updateOrder) : LightComponent(controlKey) {}

void DirectionalLightComponent::update(const float& deltaTime)
{
	//LightComponent::update(deltaTime);

	vec3 dir = owningGameObject->getFowardDirection(WORLD);

	SharedLighting::setPositionOrDirection(lightIndex, -vec4(dir, 0.0));

}