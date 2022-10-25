#include "PositionalLightComponent.h"

PositionalLightComponent::PositionalLightComponent(int controlKey, int updateOrder) : LightComponent(controlKey) {}

void PositionalLightComponent::update(const float& deltaTime)
{
	//LightComponent::update(deltaTime);

	vec3 pos = owningGameObject->getPosition(WORLD);
	SharedLighting::setPositionOrDirection(lightIndex, vec4(pos, 1.0));
	
}