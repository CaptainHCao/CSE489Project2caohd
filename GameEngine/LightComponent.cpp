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
	setAmbientColor(vec4(0.1, 0.1, 0.1, 1.0));
	setDiffuseColor(WHITE_RGBA);
	setSpecularColor(WHITE_RGBA);
	setEnabled(true);
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

void LightComponent::setEnabled(bool on) 
{
	SharedLighting::setEnabled(lightIndex, on);
}

bool LightComponent::getEnabled()
{
	return SharedLighting::getEnabled(lightIndex);
}

void LightComponent::setAttenuation(vec3 factors)
{
	SharedLighting::setAttenuationFactors(lightIndex, factors);
}

void LightComponent::setSpotCutoffCos(float cutoffCos)
{
	SharedLighting::setSpotCutoffCos(lightIndex, cutoffCos);
}

void LightComponent::setSpotDirection(glm::vec3 spotDirect)
{
	SharedLighting::setSpotDirection(lightIndex, spotDirect);
}

LightComponent::~LightComponent() {
	SharedLighting::initilizeAttributes(lightIndex);
	SharedLighting::lights[lightIndex].inUse = false;
}

void LightComponent::update(const float& deltaTime) 
{
	
}

void LightComponent::processInput()
{
	if (glfwGetKey(glfwGetCurrentContext(), controlKey) && KeyDown == false)
	{
		cout << "toggling" << endl;
		KeyDown = true;

		if (getEnabled())
		{
			setEnabled(false);
		}
		else setEnabled(true);
	}
	else if (!glfwGetKey(glfwGetCurrentContext(), controlKey))
	{
		KeyDown = false;
	}
}