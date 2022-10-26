#include "SharedTransformations.h"
#include "CameraComponent.h"
#include "SceneGraphNode.h"

//constructor
CameraComponent::CameraComponent(const int& depth, const float& vertFovDegrees,
	const float& nearClip, const float& farClip) : Component(), cameraDepth(depth), vertFovRadians(glm::radians(vertFovDegrees)), nearClip(nearClip), farClip(farClip)
{
	addCamera();
	//setCameraTransformations();
}

std::vector<CameraComponent*> CameraComponent::activeCameras;

//set the transformations, including updated viewport
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

//add a camera component

void CameraComponent::addCamera()
{
	activeCameras.push_back(this);

	//std::sort(activeCameras.begin(), activeCameras.end(), CameraComponent::CompareUpdateOrder);
	std::sort(activeCameras.begin(), activeCameras.end(), [](const auto& cam1, const auto& cam2) {return cam1->cameraDepth < cam2->cameraDepth; } );
}

// remove a camera component
void CameraComponent::removeCamera() 
{
	auto camera = find(activeCameras.begin(), activeCameras.end(), this);

	activeCameras.erase(camera);
}

//destructor of a camera component
CameraComponent::~CameraComponent()
{
	removeCamera();
}

// return the vector of active cameras
const std::vector<CameraComponent*> CameraComponent::GetActiveCameras()
{
	return activeCameras;
}

// set view port properties
void CameraComponent::setViewPort(GLfloat xLowerLeft, GLfloat yLowerLeft,
	GLfloat viewPortWidth, GLfloat viewPortHeight) 
{
	this->xLowerLeft = xLowerLeft;
	this->yLowerLeft = yLowerLeft;
	this->viewPortWidth = viewPortWidth;
	this->viewPortHeight = viewPortHeight;
	//glViewport(this->xLowerLeft * width, this->yLowerLeft * height, this->viewPortWidth * width, this->viewPortHeight * height);
}