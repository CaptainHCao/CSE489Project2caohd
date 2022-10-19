#pragma once
#include "MeshComponent.h"

class SphereMeshComponent : public MeshComponent
{
public:
	SphereMeshComponent(GLuint shaderProgram, Material mat, float radius = 1.0f, int stacks = 12, 
						int slices = 16, int updateOrder = 100);

	virtual void buildMesh() override;

protected:

	float sliceInc, stackInc, radius;
	int slices, stacks;
	Material sphereMat;

	void initializeTopSubMesh();
	void initializeBottomSubMesh();
	void initializeBodySubMesh();

};

