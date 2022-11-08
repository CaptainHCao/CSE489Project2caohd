#include "SoundListenerComponent.h"

SoundListenerComponent::SoundListenerComponent(int updateOrder) : SoundBaseComponent(updateOrder) {};

void SoundListenerComponent::update(const float& deltaTime)
{
	SoundBaseComponent::update( deltaTime );
	
	SoundEngine::check_al_errors();
}

void SoundListenerComponent::initialize() 
{

}

