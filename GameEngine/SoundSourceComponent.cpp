#include "SoundSourceComponent.h"

//constructor
SoundSourceComponent::SoundSourceComponent(std::string soundFileName, float refDistance,
	float rollOffFactor, float maxDistance, int updateOrder) : SoundBaseComponent(updateOrder) 
{
	// Load the sound file into a buffer.
	buffer = alutCreateBufferFromFile(soundFileName.c_str());
	SoundEngine::check_alut_errors();

	// Create a source
	alGenSources((ALuint)1, &source);
	SoundEngine::check_al_errors();
	// Associate the buffer with the source
	alSourcei(source, AL_BUFFER, buffer);

	setReferenceDistance(refDistance);
	setRollOffFactor(rollOffFactor);
	setMaxDistance(maxDistance);

	SoundEngine::check_al_errors();
}

//destructor
SoundSourceComponent::~SoundSourceComponent() 
{
	alSourcei(source, AL_BUFFER, NULL);
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
}

//update override
void SoundSourceComponent::update(const float& deltaTime)
{
	SoundBaseComponent::update(deltaTime);

	//set up the orientation array
	float orientation[6];
	orientation[0] = this->soundForward.x; //forward vector x value
	orientation[1] = this->soundForward.y; //forward vector y value
	orientation[2] = this->soundForward.z; //forward vector z value
	orientation[3] = this->soundUp.x; //up vector x value
	orientation[4] = this->soundUp.y; //up vector y value
	orientation[5] = this->soundUp.z; //up vector z value

	//set the position, velocity and orientation
	alSource3f(this->source, AL_POSITION, soundPosition.x, soundPosition.y, soundPosition.z);
	alSource3f(this->source, AL_VELOCITY, soundVelocity.x, soundVelocity.y, soundVelocity.z);
	alSource3f(this->source, AL_DIRECTION, soundForward.x, soundForward.y, soundForward.z);
	alSourcefv(this->source, AL_ORIENTATION, orientation);

	SoundEngine::check_al_errors();
}

void SoundSourceComponent::play()
{
	alSourcePlay(source);
}

void SoundSourceComponent::pause()
{
	alSourcePause(source);
}

void SoundSourceComponent::continuePlaying()
{
	alSourcePlay(source);
}

void SoundSourceComponent::stop()
{
	alSourceStop(source);
}

bool SoundSourceComponent::isPlaying()
{
	ALint playing;
	alGetSourcei(this->source, AL_SOURCE_STATE, &playing);
	return playing == AL_PLAYING;
}

void SoundSourceComponent::setGain(float volume) 
{
	alSourcef(this->source, AL_GAIN, volume);
}

bool SoundSourceComponent::isPaused()
{
	ALint pause;
	alGetSourcei(this->source, AL_SOURCE_STATE, &pause);
	return pause == AL_PAUSED;
}

void SoundSourceComponent::setLooping(bool loopingOn)
{
	alSourcei(this->source, AL_LOOPING, loopingOn);
}

void SoundSourceComponent::setReferenceDistance(float refDistance)
{
	alSourcef(this->source, AL_REFERENCE_DISTANCE, refDistance);
}

//initialize the position, velocity and direction
void SoundSourceComponent::initialize()
{
	//set source position
	alSource3f(source, AL_POSITION, soundPosition.x, soundPosition.y, soundPosition.z);
	//set source velocity
	alSource3f(source, AL_VELOCITY, soundVelocity.x, soundVelocity.y, soundVelocity.z);
	// Set source direction
	alSource3f(source, AL_DIRECTION, soundForward.x, soundForward.y, soundForward.z);
}

void SoundSourceComponent::setRollOffFactor(float rollOffFactor)
{
	alSourcef(this->source, AL_ROLLOFF_FACTOR, rollOffFactor);
}

void SoundSourceComponent::setMaxDistance(float maxDistance)
{
	alSourcef(this->source, AL_MAX_DISTANCE, maxDistance);
}

