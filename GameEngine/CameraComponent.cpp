#include "SharedTransformations.h"
#include "CameraComponent.h"
#include "SceneGraphNode.h"

CameraComponent::CameraComponent(const int& depth, const float& vertFovDegrees,
	const float& nearClip, const float& farClip) : Component(), cameraDepth(depth), vertFovRadians(glm::radians(vertFovDegrees)), nearClip(nearClip), farClip(farClip) {}

std::vector<CameraComponent*> CameraComponent::activeCameras;

void CameraComponent::setCameraTransformations()
{
	glm::ivec2 dim = owningGameObject->getOwningGame()->getWindowDimensions();
	float aspect = dim.x / dim.y;
	mat4 projMat = glm::perspective(vertFovRadians, aspect, nearClip, farClip);
	SharedTransformations::setProjectionMatrix(projMat);

	mat4 viewingTrans = glm::lookAt(vec3(0.0f, 50.0f, 00.0f), vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, -1.0f));

	SharedTransformations::setViewMatrix(viewingTrans);

	mat4 modelMat = owningGameObject->getModelingTransformation();

	SharedTransformations::setModelingMatrix(modelMat);
}
	
void CameraComponent::addCamera()
{
	activeCameras.push_back(this);
}

void CameraComponent::removeCamera() 
{
	auto camera = find(activeCameras.begin(), activeCameras.end(), this);

	activeCameras.erase(camera);
}

CameraComponent::~CameraComponent()
{
	removeCamera();
}

const std::vector<CameraComponent*> CameraComponent::GetActiveCameras()
{
	return activeCameras;
}

void CameraComponent::setViewPort(GLfloat xLowerLeft, GLfloat yLowerLeft,
	GLfloat viewPortWidth, GLfloat viewPortHeight) 
{
	glViewport(xLowerLeft, yLowerLeft, viewPortWidth, viewPortHeight);
}