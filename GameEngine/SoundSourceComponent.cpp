#include "SoundSourceComponent.h"

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
	SoundEngine::check_al_errors();
}

SoundSourceComponent::~SoundSourceComponent() 
{
	
}

void SoundSourceComponent::update(const float& deltaTime)
{
	SoundBaseComponent::update(deltaTime);
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

