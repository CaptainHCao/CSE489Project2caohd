#include "ReparentComponent.h"
#define VERBOSE false

//constructor
ReparentComponent::ReparentComponent(GameObject* newParent, float radius, int updateOrder)
	: Component(updateOrder), newParent(newParent), radius(radius)
{
	//componentType = MOVE;
}

//override update
void ReparentComponent::update(const float& deltaTime)
{
	//if the distance is within the radius, carry out the reparenting
	if (distanceToNewParent() < radius) 
	{
		reparent();
	}
}

//return the distance to the potential new parent
GLfloat ReparentComponent::distanceToNewParent()
{
	GLfloat dist = glm::distance(newParent->getPosition(), owningGameObject->getPosition(WORLD));

	if (VERBOSE) cout << dist << endl;

	return dist;

}

//carry out the reparenting
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
}//end the reparenting process