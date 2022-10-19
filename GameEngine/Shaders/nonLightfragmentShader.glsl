// Targeting version 4.5 of GLSL. If the compiler does not support 4.5 it will cause an error.
#version 450 core

in vec3 worldPos;
in vec3 worldNorm;
in vec2 texCoord0;
out vec4 fragmentColor;

layout(shared) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};

struct Material
{
	vec4 ambientMat;
	vec4 diffuseMat;
	vec4 specularMat;
	vec4 emmissiveMat;
	float specularExp;
	int textureMode;
	bool diffuseTextureEnabled;
	bool specularTextureEnabled;
};

layout(shared) uniform MaterialBlock
{
	Material object;
};


layout(binding = 0) uniform sampler2D diffuseSampler;
layout(binding = 1) uniform sampler2D specularSampler;

void main()
{
	 if(object.diffuseTextureEnabled) {

		fragmentColor = texture( diffuseSampler, texCoord0 );

	 }
	 else {
		fragmentColor = object.diffuseMat;

	 }

}