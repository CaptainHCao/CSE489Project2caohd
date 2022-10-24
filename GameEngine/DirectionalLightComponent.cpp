#include "DirectionalLightComponent.h"

void DirectionalLightComponent::update(const float& deltaTime)
{
	vec3 dir = owningGameObject->getFowardDirection(WORLD);

	SharedLighting::setPositionOrDirection(lightIndex, -vec4(dir, 1.0));

}