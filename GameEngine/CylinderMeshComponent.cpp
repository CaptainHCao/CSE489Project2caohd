#include "CylinderMeshComponent.h"

//constructor
CylinderMeshComponent::CylinderMeshComponent(GLuint shaderProgram, Material mat,
	float radius, float height, int stacks,
	int slices, int updateOrder)
	: cylinderMat(mat), MeshComponent(shaderProgram, updateOrder),
	radius(radius), height(height), stacks(stacks), slices(slices)
{

}

void CylinderMeshComponent::buildMesh()
{
	//cylinder name
	this->scaleMeshName = "Cylinder " + std::to_string(radius) + " " +
		std::to_string(height) + " " + std::to_string(stacks) + std::to_string(slices) + std::to_string(this->cylinderMat._id);

	if (previsouslyLoaded() == false) {

		//stores vertex data
		std::vector<pntVertexData> vData;
		std::vector<pntVertexData> vDataTop;
		std::vector<pntVertexData> vDataBot;
		std::vector<unsigned int> indices;
		std::vector<unsigned int> indicesTop;
		std::vector<unsigned int> indicesBot;

		//increaments
		float angleInc = (2 * PI)/ this->slices;
		float stackInc = this->height / this->stacks;

		//current height and angle
		float stackHeight = -(this->height) / 2;
		float angle = 0.0f;
		int count = 0;
		int countTop = 0;
		int countBot = 0;

		//vector variables for top and bot faces
		vec4 centerTopVector = vec4(0, (this->height) / 2 + stackInc, 0, 1.0f);
		vec3 normalTop = vec3(0, 1, 0);
		vec4 centerBotVector = vec4(0, stackHeight + stackInc, 0, 1.0f);
		vec3 normalBot = vec3(0, -1, 0);
		vec2 centerTexture = vec2(0.5, 0.5);

		// First loop increasing the height (stacks)
		for (int j = 0; j < this->stacks; j++) {
			
			stackHeight += stackInc;

			//texture coordinates pnt1, pnt0
			vec2 t0 = vec2(angle / ( 2 * PI ), (stackHeight + stackInc + this->height/2) / this->height);
			vec2 t1 = vec2(angle / (2 * PI), (stackHeight  + this->height / 2) / this->height);

			// vertex position pnt0, pnt1
			vec4 v0 = vec4(cos(angle) * this->radius, stackHeight + stackInc, sin(angle) * this->radius, 1.0f);
			vec4 v1 = vec4(cos(angle) * this->radius, stackHeight, sin(angle) * this->radius, 1.0f);

			//initialize the normal vector for all sided triangle
			vec3 normal = normalize(vec3(cos(angle), 0, sin(angle)));

			//update pnt0 and pnt1
			pntVertexData pnt0(v0, normal, t0);
			pntVertexData pnt1(v1, normal, t1);

			//temporary holding variables for top and bot texturing
			vec2 t = vec2(0.5 * (1 - cos(angle)), 0.5 * (1 - sin(angle)));
			pntVertexData pnt00(v0, normal, t);
			pntVertexData pnt01(v1, normal, t);

			// Second loop increasing the angle inside 1 stack
			for (int i = 0; i < this->slices; i++) {

				angle += angleInc;

				//update the normal vector. Just in case
				normal = normalize(vec3(cos(angle), 0, sin(angle)));

				//texture coordinates pnt2, pnt3
				vec2 t2 = vec2(angle / (2 * PI), (stackHeight + this->height / 2) / this->height);
				vec2 t3 = vec2(angle / (2 * PI), (stackHeight + stackInc + this->height / 2) / this->height);

				// vertex position pnt2, pnt3
				vec4 v2 = vec4(cos(angle) * radius, stackHeight, sin(angle) * radius, 1.0f);
				vec4 v3 = vec4(cos(angle) * radius, stackHeight + stackInc, sin(angle) * radius, 1.0f);

				//update pnt2 and pnt3
				pntVertexData pnt2(v2, normal, t2);
				pntVertexData pnt3(v3, normal, t3);

				//temporary holding variables for top and bot texturing 
				t = vec2(0.5 * (1 - cos(angle)), 0.5 * (1 - sin(angle)));
				pntVertexData pnt02(v2, normal, t);
				pntVertexData pnt03(v3, normal, t);
				 

				//top stack
				if (j == this->stacks - 1) {
					pntVertexData centerTop(centerTopVector, normalTop, centerTexture);
					vDataTop.push_back(centerTop);
					vDataTop.push_back(pnt03);
					vDataTop.push_back(pnt00);
					
					indicesTop.push_back(0 + countTop * 3);
					indicesTop.push_back(1 + countTop * 3);
					indicesTop.push_back(2 + countTop * 3);

					countTop++;
				}
				//bot stack
				else if (j == 0) {
					pntVertexData centerBot(centerBotVector, normalBot, centerTexture);
					vDataBot.push_back(centerBot);
					vDataBot.push_back(pnt01);
					vDataBot.push_back(pnt02);

					indicesBot.push_back(0 + countBot * 3);
					indicesBot.push_back(1 + countBot * 3);
					indicesBot.push_back(2 + countBot * 3);

					countBot++;
				}

				//push back vertices to create triangles around the body
				vData.push_back(pnt0);
				vData.push_back(pnt1);
				vData.push_back(pnt2);
				vData.push_back(pnt3);

				indices.push_back(0 + 4 * count);
				indices.push_back(3 + 4 * count);
				indices.push_back(1 + 4 * count);

				indices.push_back(1 + 4 * count);
				indices.push_back(3 + 4 * count);
				indices.push_back(2 + 4 * count);

				count++;

				// Pass 2 vertex values to the next triangle
				pnt0 = pnt3;
				pnt1 = pnt2;

				pnt00 = pnt03;
				pnt01 = pnt02;
			}

		}
		

		SubMesh cylinderMesh = MeshComponent::buildSubMesh(vData, indices);
		SubMesh cylinderMeshTop = MeshComponent::buildSubMesh(vDataTop, indicesTop);
		SubMesh cylinderMeshBot = MeshComponent::buildSubMesh(vDataBot, indicesBot);

		//SubMesh cylinderMesh = buildSubMesh(vData);

		//set primitive mode for vextex data
		cylinderMesh.primitiveMode = GL_TRIANGLES;
		cylinderMeshTop.primitiveMode = GL_TRIANGLES;
		cylinderMeshBot.primitiveMode = GL_TRIANGLES;

		//set material 
		cylinderMesh.material = this->cylinderMat;
		cylinderMeshTop.material = this->cylinderMat;
		cylinderMeshBot.material = this->cylinderMat;

		//push to render the cylinder
		this->subMeshes.push_back(cylinderMeshTop);
		this->subMeshes.push_back(cylinderMesh);
		this->subMeshes.push_back(cylinderMeshBot);

		this->saveInitialLoad();
	}

} // end initialize 
