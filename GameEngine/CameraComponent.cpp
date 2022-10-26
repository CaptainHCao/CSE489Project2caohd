#include "SharedTransformations.h"
#include "CameraComponent.h"
#include "SceneGraphNode.h"

CameraComponent::CameraComponent(const int& depth, const float& vertFovDegrees,
	const float& nearClip, const float& farClip) : Component(), cameraDepth(depth), vertFovRadians(glm::radians(vertFovDegrees)), nearClip(nearClip), farClip(farClip)
{
	addCamera();
	//setCameraTransformations();
}

std::vector<CameraComponent*> CameraComponent::activeCameras;

void CameraComponent::setCameraTransformations()
{
	glm::ivec2 dim = owningGameObject->getOwningGame()->getWindowDimensions();
	float aspect = dim.x / dim.y;
	mat4 projMat = glm::perspective(vertFovRadians, aspect, nearClip, farClip);
	SharedTransformations::setProjectionMatrix(projMat);

	mat4 modelMat = owningGameObject->getModelingTransformation();

	SharedTransformations::setModelingMatrix(modelMat);

	/*mat4 viewingTrans = glm::lookAt(vec3(0.0f, 50.0f, 00.0f), vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 0.0f, -1.0f));*/
	mat4 viewingTrans = glm::inverse(modelMat);
	SharedTransformations::setViewMatrix(viewingTrans);

	glViewport(this->xLowerLeft * dim.x, this->yLowerLeft * dim.y, this->viewPortWidth * dim.x, this->viewPortHeight * dim.y);
}

	
void CameraComponent::addCamera()
{
	activeCameras.push_back(this);
	std::sort(activeCameras.begin(), activeCameras.end(), CameraComponent::CompareUpdateOrder);
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
	this->xLowerLeft = xLowerLeft;
	this->yLowerLeft = yLowerLeft;
	this->viewPortWidth = viewPortWidth;
	this->viewPortHeight = viewPortHeight;
	//glViewport(this->xLowerLeft * width, this->yLowerLeft * height, this->viewPortWidth * width, this->viewPortHeight * height);
}