#include "SphereMeshComponent.h"

vec4 sphericalToCartesian(float sliceAngle, float stackAngle,
	float radius)
{
	vec4 v(glm::cos(stackAngle) * glm::sin(sliceAngle) * radius,
		glm::sin(stackAngle) * radius,
		glm::cos(stackAngle) * cos(sliceAngle) * radius,
		1.0f);

	return v;

} // end sphericalToCartesian


SphereMeshComponent::SphereMeshComponent(GLuint shaderProgram, Material mat, float radius, int stacks, int slices, int updateOrder)
	: MeshComponent(shaderProgram, updateOrder), sphereMat(mat), radius(radius), stacks(stacks), slices(slices)
{
	sliceInc = (2.0f * PI) / slices;
	stackInc = PI / stacks;

}

void SphereMeshComponent::buildMesh()
{
	this->scaleMeshName = "Sphere " + std::to_string(radius) + std::to_string(this->sphereMat._id);

	if (previsouslyLoaded() == false) {

		initializeTopSubMesh();

		initializeBodySubMesh();

		initializeBottomSubMesh();

		this->saveInitialLoad();
	}

}

void SphereMeshComponent::initializeTopSubMesh()
{
	std::vector<pntVertexData> pnt;

	float sliceAngle = 0.0f;

	vec4 top = vec4(0.0f, radius, 0.0f, 1.0f);
	vec4 v = sphericalToCartesian(sliceAngle, PI_OVER_2 - stackInc, radius);

	pntVertexData pntTop(top, glm::normalize(top).xyz, ZERO_V2);
	pntVertexData pntV(v, glm::normalize(v).xyz, ZERO_V2);

	pnt.push_back(pntTop);
	pnt.push_back(pntV);

	for (int j = 0; j < slices; j++) {

		sliceAngle += sliceInc;
		v = sphericalToCartesian(sliceAngle, PI_OVER_2 - stackInc, radius);

		pntVertexData pntV(v, glm::normalize(v).xyz, ZERO_V2);

		pnt.push_back(pntV);
	}

	SubMesh subMesh = buildSubMesh(pnt);

	// Set the primitive mode for the vertex data
	subMesh.primitiveMode = GL_TRIANGLE_FAN;

	subMesh.material = sphereMat;

	// Push the submesh into vector of Submeshes to be rendered
	this->subMeshes.push_back(subMesh);


}
void SphereMeshComponent::initializeBottomSubMesh()
{
	std::vector<pntVertexData> pnt;

	float sliceAngle = glm::radians(360.0f);

	vec4 bottom = vec4(0.0f, -radius, 0.0f, 1.0f);
	vec4 v = sphericalToCartesian(sliceAngle, -PI_OVER_2 + stackInc, radius);

	pntVertexData pntbottom(bottom, glm::normalize(bottom).xyz, ZERO_V2);
	pntVertexData pntV(v, glm::normalize(v).xyz, ZERO_V2);

	pnt.push_back(pntbottom);
	pnt.push_back(pntV);

	for (int j = 0; j < slices; j++) {

		sliceAngle -= sliceInc;
		v = sphericalToCartesian(sliceAngle, -PI_OVER_2 + stackInc, radius);

		pntVertexData pntV(v, glm::normalize(v).xyz, ZERO_V2);

		pnt.push_back(pntV);
	}

	SubMesh subMesh = buildSubMesh(pnt);

	// Set the primitive mode for the vertex data
	subMesh.primitiveMode = GL_TRIANGLE_FAN;

	subMesh.material = sphereMat;

	// Push the submesh into vector of Submeshes to be rendered
	this->subMeshes.push_back(subMesh);

}
void SphereMeshComponent::initializeBodySubMesh() 
{
	std::vector<pntVertexData> pnt;

	float stackAngle = -PI_OVER_2 + stackInc;

	for (int j = 0; j < stacks-2; j++) {

		float sliceAngle = 0.0f;

		vec4 v0 = sphericalToCartesian(sliceAngle, stackAngle + stackInc, radius);
		vec4 v1 = sphericalToCartesian(sliceAngle, stackAngle, radius);

		pntVertexData pnt0(v0, glm::normalize(v0).xyz, ZERO_V2);
		pntVertexData pnt1(v1, glm::normalize(v1).xyz, ZERO_V2);

		for (int i = 0; i < slices; i++) {

			sliceAngle += sliceInc;

			vec4 v2 = sphericalToCartesian(sliceAngle, stackAngle, radius);
			vec4 v3 = sphericalToCartesian(sliceAngle, stackAngle + stackInc, radius);

			pntVertexData pnt2(v2, glm::normalize(v2).xyz, ZERO_V2);
			pntVertexData pnt3(v3, glm::normalize(v3).xyz, ZERO_V2);

			pnt.push_back(pnt0);
			pnt.push_back(pnt1);
			pnt.push_back(pnt3);

			pnt.push_back(pnt1);
			pnt.push_back(pnt2);
			pnt.push_back(pnt3);

			pnt0 = pnt3;
			pnt1 = pnt2;
		}

		stackAngle += stackInc;
	}

	SubMesh subMesh = buildSubMesh(pnt);

	// Set the primitive mode for the vertex data
	subMesh.primitiveMode = GL_TRIANGLES;

	subMesh.material = sphereMat;

	// Push the submesh into vector of Submeshes to be rendered
	this->subMeshes.push_back(subMesh);

}