#include "SpotLightComponent.h"

void SpotLightComponent::update(const float& deltaTime)
{
	vec3 pos = owningGameObject->getPosition(WORLD);

	vec3 dir = owningGameObject->getFowardDirection(WORLD);

	SharedLighting::setPositionOrDirection(lightIndex, vec4(pos, 1.0));

	SharedLighting::setSpotDirection(lightIndex, dir);

}