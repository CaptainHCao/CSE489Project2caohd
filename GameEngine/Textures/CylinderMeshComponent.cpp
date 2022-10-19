#include "CylinderMeshComponent.h"

CylinderMeshComponent::CylinderMeshComponent(GLuint shaderProgram, Material mat, float radius, float height, int stacks, int slices, int updateOrder) 
	: cylinderMat(mat), MeshComponent(shaderProgram, updateOrder), radius(radius), height(height), slices(slices), stacks(stacks)
{

}

void CylinderMeshComponent::buildMesh()
{
	std::vector<pntVertexData> pnt;

	float stackCounter = -height / 2.0f;
	float stackInc = 1.0f;
	float sliceInc = PI / 6;
	//float sliceHeight = stackCounter + stackInc;

	float sliceAngle = 0.0f;

	
	vec4 v0 = vec4(cos(sliceAngle) * radius, stackCounter + stackInc, sin(sliceAngle) * radius, 1.0f);
	vec4 v1 = vec4(cos(sliceAngle) * radius, stackCounter, sin(sliceAngle) * radius, 1.0f);

	vec3 n1 = vec3(0, -1, 0);
	vec3 n2 = vec3(0, 1, 0);
	vec3 n3 = vec3(cos(sliceAngle), 0, sin(sliceAngle));


	vec2 t0;
	vec2 t1;
	vec2 t2;
	vec2 t3;


	pntVertexData pnt0(v0, n1, ZERO_V2);
	pntVertexData pnt1(v1, n1, ZERO_V2);



	for (int i = 0; i < stacks; i++) {

		stackCounter += stackInc;




	}


	for (int i = 0; i < slices; i++) {

		sliceAngle += sliceInc;
		

		vec4 v2 = vec4(cos(sliceAngle) * radius, stackCounter, sin(sliceAngle) * radius, 1.0f);
		vec4 v3 = vec4(cos(sliceAngle) * radius, stackCounter + stackInc, sin(sliceAngle) * radius, 1.0f);

		vec3 n4 = vec3(cos(sliceAngle), 0, sin(sliceAngle));

		pntVertexData pnt2(v2, n1, ZERO_V2);
		pntVertexData pnt3(v3, n1, ZERO_V2);

		pnt.push_back(pnt0);
		pnt.push_back(pnt3);
		pnt.push_back(pnt1);

		pnt.push_back(pnt1);
		pnt.push_back(pnt3);
		pnt.push_back(pnt2);

		pnt0 = pnt3;
		pnt1 = pnt2;
	}




	SubMesh subMesh = buildSubMesh(pnt);

	// Set the primitive mode for the vertex data
	subMesh.primitiveMode = GL_TRIANGLES;

	subMesh.material = cylinderMat;

	// Push the submesh into vector of Submeshes to be rendered
	this->subMeshes.push_back(subMesh);

	}


	

