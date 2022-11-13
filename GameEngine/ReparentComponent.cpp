#include "ReparentComponent.h"
#define VERBOSE false

ReparentComponent::ReparentComponent(GameObject* newParent, float radius, int updateOrder)
	: Component(updateOrder), newParent(newParent), radius(radius)
{
	//componentType = MOVE;
}

void ReparentComponent::update(const float& deltaTime)
{
	if (distanceToNewParent() < radius) 
	{
		reparent();
	}
}

GLfloat ReparentComponent::distanceToNewParent()
{
	GLfloat dist = glm::distance(newParent->getPosition(), owningGameObject->getPosition(WORLD));

	if (VERBOSE) cout << dist << endl;

	return dist;

}

GLvoid ReparentComponent::reparent()
{
	std::vector<Component*> components;

	components = owningGameObject->getComponents();
	for (Component* component : components)
	{
		if (component->getComponentType() == MOVE)
		{
			owningGameObject->removeComponent(component);
		}
	}

	newParent->reparent(owningGameObject);
	owningGameObject->setPosition(vec3(0.0f, 0.0f, 0.0f), LOCAL);

	for (Component* component : components)
	{
		if (component->getComponentType() == MOVE)
		{
			owningGameObject->addComponent(component);
		}
	}
}