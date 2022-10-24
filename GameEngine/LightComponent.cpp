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

void LightComponent::setAmbientColor(vec4 mat) 
{ 
	SharedLighting::setAmbientColor(lightIndex, mat);
}

void LightComponent::setDiffuseColor(vec4 mat) 
{
	SharedLighting::setDiffuseColor(lightIndex, mat);
}

void LightComponent::setSpecularColor(vec4 mat) 
{
	SharedLighting::setSpecularColor(lightIndex, mat);
}

LightComponent::~LightComponent() {
	SharedLighting::initilizeAttributes(lightIndex);
	SharedLighting::lights[lightIndex].inUse = false;
}

void LightComponent::update(const float& deltaTime) 
{

}