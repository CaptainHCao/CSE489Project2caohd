#pragma once
#include <string>
#include <unordered_map>

#include "MathLibsConstsFuncs.h"
#include "Component.h"
#include "Material.h"

using namespace constants_and_types;

/**
 * @struct	pntVertexData
 *
 * @brief	Structure for holding vertex data for a single vertex. The data 
 * 			includes a position, normal vector, and texture coordinate.
 */
struct pntVertexData
{
	// Position of the vertex in Object coordinates
	glm::vec4 m_pos;

	// Normal vector for the vertex in Object coordinates
	glm::vec3 m_normal;

	// 2D vertex texture coordinates
	glm::vec2 m_textCoord;

	pntVertexData(glm::vec4 pos = ZERO_V4,
		glm::vec3 normal = ZERO_V3,
		glm::vec2 textCoord = ZERO_V2)
	{
		m_pos = pos;
		m_normal = normal;
		m_textCoord = textCoord;
	}
};


/**
 * @enum	RENDER_MODE
 *
 * @brief	Values that represent render modes to be used when a sub-mesh if rendered.
 */
enum RENDER_MODE { ORDERED, INDEXED };

/**
 * @struct	SubMesh
 *
 * @brief	stuct containing values needed to render a sub-mesh. All visible objects
 * 			(Meshes) are rendered using one or more sub-meshes.
 */
struct SubMesh {

	GLuint vao = GL_INVALID_VALUE; // ID for Vertex Array Object for the sub-mesh

	GLuint vertexBuffer = GL_INVALID_VALUE; // ID for vertex data buffer for the sub-mesh

	GLuint indexBuffer = GL_INVALID_VALUE; // ID for index buffer for the sub-mesh (if indexed rendering is used)

	GLuint count = 0; // Either the number of vertices in the mesh or the number of indices

	RENDER_MODE renderMode = INDEXED; // Render mode for the mesh. Either ORDERED or INDEXED

	GLenum primitiveMode = GL_TRIANGLES; // Primitive mode for the mesh GL_POINTS, GL_LINES, etc.

	Material material;  // Material properties used to render the object

}; // end SubMesh

/**
 * @struct	BaseMeshLoad
 *
 * @brief	Structure that represents a previously loaded mesh and how many copies
 * 			have been loaded. Stores all the submeshes needed to render the meshes
 * 			and how many copies have been loaded.
 */
struct BaseMeshLoad {

	std::vector<SubMesh> modelSubMeshes;

	int copyCount = 0;
};


/**
 * @class	Mesh
 *
 * @brief	Base class for all objects that will appear visually in the scene. All 
 * 			MeshComponents are rendered using one or more sub-meshes.
 */
class MeshComponent : public Component
{
public: 

	// ****** Temporary **********

	// bool active = true;//******************* Week 8 ********************

	// mat4 modelingTransformation = mat4(1.0f); //******************* Week 8 ********************


	// ****** End Temporary **********

	/**
	 * @fn	MeshComponent::MeshComponent(GLuint shaderProgram, int updateOrder = 100)
	 *
	 * @brief	Constructor
	 *
	 * @param 	shaderProgram	Shader program that will be used to render the mesh.
	 * @param 	updateOrder  	(Optional) The update order of the component.
	 */
	MeshComponent(GLuint shaderProgram, int updateOrder = 100)
		: shaderProgram(shaderProgram), Component(updateOrder)
	{
		componentType = MESH;
	};

	/**
	 * @fn	MeshComponent::virtual~MeshComponent();
	 *
	 * @brief	Destructor. Deletes all dynamically allocated data.
	 */
	virtual~MeshComponent();

	/**
	 * @fn	virtual void MeshComponent::buildMesh() = 0;
	 *
	 * @brief	Buffers all the data that is associated with the vertex data for this object. Creates
	 * 			a Vertex Array Object that holds references to the vertex buffers, the index buffer
	 * 			and the layout specification. This is a pure virtual method and must be overridden.
	 */
	virtual void buildMesh() = 0;

	/**
	 * @fn	virtual void Mesh::draw();
	 *
	 * @brief	Renders all sub-meshes that are part of the object. Binds
	 * 			the vertex array object, sets the material properties, and sets
	 * 			the modeling transformation based on the world transformation
	 * 			of the owning game object.
	 */
	virtual void draw() const;

	/**
	 * @fn	void Game::addMeshComp(class MeshComponent* mesh);
	 *
	 * @brief	Adds this mesh component to the Game
	 *
	 * @param [in,out]	mesh	If non-null, the mesh.
	 */
	void addMeshComp();

	/**
	 * @fn	void Game::removeMeshComp(class MeshComponent* mesh);
	 *
	 * @brief	Removes this mesh component from the Game
	 *
	 * @param [in,out]	mesh	If non-null, the mesh.
	 */
	void removeMeshComp();

	/**
	 * @fn	static std::vector<class MeshComponent*> MeshComponent::GetMeshComponents();
	 *
	 * @brief	Gets all the currently loaded mesh components
	 *
	 * @returns	Null if it fails, else the vector containing all mesh components
	 * 			that should be rendered.
	 */
	static const std::vector<class  MeshComponent*> GetMeshComponents();

protected:

	/**
	 * @fn	SubMesh MeshComponent::buildSubMesh(const std::vector<pcVertexData>& vertexData);
	 *
	 * @brief	Builds one sub mesh  that will be rendered using sequential rendering based the
	 * 			vertex data that are passed to it. The vertex data is loaded into a buffer located in
	 * 			GPU memory.
	 *
	 * @param 	vertexData	Information describing the vertex.
	 *
	 * @returns	A SubMesh.
	 */
	SubMesh buildSubMesh(const std::vector<pntVertexData>& vertexData);

	/**
	 * @fn	SubMesh MeshComponent::buildSubMesh(const std::vector<pcVertexData>& vertexData, const std::vector<unsigned int>& indices);
	 *
	 * @brief	Builds one sub mesh  that will be rendered using indexed rendering based the vertex
	 * 			data, indices, and material properties that are passed to it. Both the vertex data
	 * 			and the indices are loaded into buffers located in GPU memory.
	 *
	 * @param 	vertexData	Information describing the vertex.
	 * @param 	indices   	indices that will be used for indexed rendering.
	 *
	 * @returns	A SubMesh.
	 */
	SubMesh buildSubMesh(const std::vector<pntVertexData>& vertexData, const std::vector<unsigned int>& indices);

	/** @brief	Indentifier for the shader program used to render all sub-meshes */
	GLuint shaderProgram = 0; 

	/** @brief	Container for all sub meshes that are part of this component.*/
	std::vector<SubMesh> subMeshes;

	/** @brief	Name of model that includes the scale. One
	copy of each model will be loaded for specified scale */
	string scaleMeshName;

	/************** Static data member used by the Game to manage MeshComponents **********/

	/** @brief	All mesh components that need to be rendered. */
	static std::vector<class MeshComponent*> meshComps;

	/** Meshes for managaging MeshComponents to keep a mesh from being loaded multiple times **/

	/**
	 * @fn	void MeshComponent::listLoadedMeshes();
	 *
	 * @brief	Prints the names of all meshes that have been loaded. Used for debugging.
	 */
	void listLoadedMeshes();

	/**
	 * @fn	bool MeshComponent::previsouslyLoaded();
	 *
	 * @brief	Determines if this mesh/model has been previously loaded
	 *
	 * @returns	True if a mesh/model with has previsously been loaded.
	 */
	bool previsouslyLoaded();

	/**
	 * @fn	void MeshComponent::saveInitialLoad();
	 *
	 * @brief	Is called when a me
	 */
	void saveInitialLoad();

	/** @brief	Map of ALL meshes that have been loaded previously.*/
	static std::unordered_map<std::string, BaseMeshLoad> loadedModels;

}; // end MeshComponent class




