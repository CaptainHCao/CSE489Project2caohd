#include "PositionalLightComponent.h"

void PositionalLightComponent::update(const float& deltaTime)
{
	vec3 pos = owningGameObject->getPosition(WORLD);
	SharedLighting::setPositionOrDirection(lightIndex, vec4(pos, 1.0));
	
}