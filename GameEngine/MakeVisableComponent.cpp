#include "MakeVisableComponent.h"


MakeVisableComponent::MakeVisableComponent(int controlKey, int updateOrder)
	: Component(updateOrder), controlKey(controlKey)
{

}

void MakeVisableComponent::initialize()
{
	owningGameObject->setState(ACTIVE);

}
void MakeVisableComponent::processInput()
{
	if (glfwGetKey(glfwGetCurrentContext(), controlKey) && KeyDown == false) {

		owningGameObject->setState(owningGameObject->getState() == ACTIVE ? PAUSED : ACTIVE); 

		KeyDown = true;

	}
	else if (!glfwGetKey(glfwGetCurrentContext(), controlKey)) {
		KeyDown = false;
	}


}