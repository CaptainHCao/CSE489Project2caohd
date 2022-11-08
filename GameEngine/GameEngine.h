#pragma once

// Base Classes
#include "GameObject.h"

// Shader program building
#include "BuildShaderProgram.h"
#include "Texture.h"

// Shared Uniform Blocks
#include "SharedMaterials.h"
#include "SharedTransformations.h"

// Meshes
#include "BoxMeshComponent.h"
#include "ModelMeshComponent.h"
#include "SphereMeshComponent.h"
#include "CylinderMeshComponent.h"
// Movement

#include "ArrowRotateComponent.h"
#include "MakeVisableComponent.h"
#include "TranslateComponent.h"
#include "ContinuousRotateComponent.h"
#include "SteerComponent.h"
#include "SteeringComponent.h"
#include "WaypointComponent.h"


// Lighting
#include "SharedLighting.h"
#include "LightComponent.h"
#include "DirectionalLightComponent.h"
#include "PositionalLightComponent.h"
#include "SpotLightComponent.h"

//Camera
#include "CameraComponent.h"

//Sound
#include "SoundEngine.h"
#include "SoundSourceComponent.h"
#include "SoundListenerComponent.h"