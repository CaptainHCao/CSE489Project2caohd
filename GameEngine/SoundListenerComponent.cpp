#include "SoundListenerComponent.h"

//constructor
SoundListenerComponent::SoundListenerComponent(int updateOrder) : SoundBaseComponent(updateOrder) {};

//update override
void SoundListenerComponent::update(const float& deltaTime)
{
	SoundBaseComponent::update( deltaTime );

	//set up the array storing otirentation data
	float orientation[6];
	orientation[0] = this->soundForward.x; //forward vector x value
	orientation[1] = this->soundForward.y; //forward vector y value
	orientation[2] = this->soundForward.z; //forward vector z value
	orientation[3] = this->soundUp.x; //up vector x value
	orientation[4] = this->soundUp.y; //up vector y value
	orientation[5] = this->soundUp.z; //up vector z value
	
	//set the position, velocity and orientation
	alListener3f(AL_POSITION, this->soundPosition.x, this->soundPosition.y, this->soundPosition.z);
	alListener3f(AL_VELOCITY, this->soundVelocity.x, this->soundVelocity.y, this->soundVelocity.z);
	alListenerfv(AL_ORIENTATION, orientation);
	
	SoundEngine::check_al_errors();
}

void SoundListenerComponent::initialize() {}

