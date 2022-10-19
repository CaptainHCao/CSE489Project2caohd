#include "LightComponent.h"
#include "SharedLighting.h"

LightComponent::LightComponent(int controlKey, int updateOrder)
	: Component(updateOrder), controlKey(controlKey)
{

	componentType = LIGHT;

	for (int i = 0; i < MAX_LIGHTS; i++) {

		if (SharedLighting::lights[i].inUse == false) {
			lightIndex = i;
			SharedLighting::lights[i].inUse = true;
			break;
		}
	}
}

LightComponent::~LightComponent() {
	SharedLighting::initilizeAttributes(lightIndex);
	SharedLighting::lights[lightIndex].inUse = false;
}