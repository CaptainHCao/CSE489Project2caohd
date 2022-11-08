#pragma once

#include "GameEngine.h" 

class MyGame : public Game
{

public:

	MyGame(std::string windowTitle = "Project 3")
		: Game(windowTitle)
	{}

protected:

	virtual void loadScene() override
	{
		// Build shader program
		ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "Shaders/vertexShader.glsl" },
		{ GL_FRAGMENT_SHADER, "Shaders/perPixelLightingfragmentShader.glsl" },
		{ GL_NONE, NULL } // signals that there are no more shaders 
		};

		// Build the shader program
		GLuint shaderProgram = BuildShaderProgram(shaders);

		// Set up the uniform bufferes and 
		SharedMaterials::setUniformBlockForShader(shaderProgram);
		SharedTransformations::setUniformBlockForShader(shaderProgram);
	
		SharedLighting::setUniformBlockForShader(shaderProgram);


		// Set the clear color for the rendering window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Create a "blue" material for a cylinder
		Material sphereMat;
		sphereMat.diffuseMat = BLUE_RGBA;

		//create texture object                              
		sphereMat.setDiffuseTexture(Texture::GetTexture("Textures/sun.jpg")->getTextureObject());

		// Instantiate a box shaped mesh
		SphereMeshComponent* sphere = new SphereMeshComponent(shaderProgram, sphereMat);

		// Create a container to hold the box
		GameObject* firstGameObject = new GameObject(); 

		//Sound component for the sun
		SoundSourceComponent* spaceSound = new SoundSourceComponent("Sounds/space.wav");
		spaceSound->play();
		spaceSound->setLooping(true);
		//SoundListenerComponent* spaceSound = new SoundListenerComponent("Sounds/space.wav");

		// Create a "blue" material for a box
		//Material boxMat;
		//boxMat.diffuseMat = BLUE_RGBA;

		//// Instantiate a box shaped mesh component
		//BoxMeshComponent* box = new BoxMeshComponent(boxMat, shaderProgram);

		// Add the box to a GameObject
		firstGameObject->addComponent(sphere); 
		firstGameObject->addComponent(new ArrowRotateComponent( 100));
		firstGameObject->addComponent(new MakeVisableComponent(GLFW_KEY_B));
		firstGameObject->addComponent(new ContinuousRotateComponent(20.0f, UNIT_Y_V3, 100));
		firstGameObject->addComponent(spaceSound);

		////Add a car
		//GameObject* secondGameObject = new GameObject();

		//secondGameObject->addComponent(new ModelMeshComponent("my_objects/car.obj", shaderProgram));
		//secondGameObject->addComponent(new TranslateComponent(vec3(-3.0f, 0.0f, -4.0f)));
		//secondGameObject->addComponent(new SteerComponent(60.0f));

	
		////third game object - a red box
		//GameObject* thirdGameObject = new GameObject();
		//Material boxMat1;
		//boxMat1.diffuseMat = RED_RGBA;

		//BoxMeshComponent* box1 = new BoxMeshComponent(boxMat1, shaderProgram, 2.0f, 2.0f, 2.0f);

		//thirdGameObject->addComponent(box1);

		////create waypoints for thridObject
		//std::vector<vec3> waypoints;
		//waypoints.push_back(vec3(10.0f, 0.0f, 5.0f));
		//waypoints.push_back(vec3(5.0f, 0.0f, 0.0f));
		//waypoints.push_back(vec3(8.0f, 0.0f, 10.0f));
		////thirdGameObject->addComponent(new WaypointComponent(waypoints));
		//thirdGameObject->addComponent(new SteeringComponent(waypoints, glm::vec3(20.0f, 0.0f, 0.0f)));
		//thirdGameObject->addComponent(new ContinuousRotateComponent(20.0f, UNIT_Y_V3, 100));

		//Create camera object
		GameObject* cameraObject = new GameObject();
		CameraComponent* firstCamera = new CameraComponent(0, 60.0);
		
		GameObject* secondCameraObject = new GameObject();
		CameraComponent* secondCamera = new CameraComponent(1, 60.0);
		secondCamera->setViewPort(0.6f, 0.6f, 0.4f, 0.4f);


		//Add component to object
		cameraObject->addComponent(firstCamera);
		//cameraObject->addComponent(new ArrowRotateComponent());
		secondCameraObject->addComponent(secondCamera);
		
		//Create a game object to hold the light
		GameObject* lightObject = new GameObject();

		//A directional light
		//LightComponent* dir = new DirectionalLightComponent(GLFW_KEY_D);

		//A positional light
		LightComponent* pos = new PositionalLightComponent(GLFW_KEY_P);
		pos->setAmbientColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		//pos->setAttenuationFactors(vec3(1.0, 0.0, 0.0));

		//A spot light
		/*LightComponent* spot = new SpotLightComponent(GLFW_KEY_S);
		spot->setSpotCutoffCos(glm::cos(glm::radians(PI_OVER_2)));
		spot->setSpotDirection(vec3(0.0f, 0.0f, -1.0f));*/

		//Add component back to the game object
		//lightObject->addComponent(dir);
		lightObject->addComponent(pos);
		//lightObject->addComponent(spot);

		// Add the game object to the game
		this->addChildGameObject(firstGameObject);
		/*this->addChildGameObject(secondGameObject);
		this->addChildGameObject(thirdGameObject);*/
		this->addChildGameObject(lightObject);
		this->addChildGameObject(cameraObject);
		this->addChildGameObject(secondCameraObject);

		//secondGameObject->addChildGameObject(cameraObject);

		// Rotate the box game object that contains the cube
		//firstGameObject->setRotation(glm::rotate(PI / 4.0f, UNIT_Y_V3)); //******************* Week 8 ********************
		//secondGameObject->setPosition(vec3(3.0f, 1.0f, 1.0f));
		//thirdGameObject->setPosition(vec3(0.0f, 0.0f, 0.0f));
		lightObject->setPosition(vec3(0.0f, 0.0f, 0.0f));
		firstGameObject->setPosition(vec3(0.0f, 0.0f, 0.0f));
		//second camera from above
		secondCameraObject->setPosition(vec3(0.0f, 30.0f, 30.0f));
		secondCameraObject->setRotation(glm::rotate(-PI/3, UNIT_X_V3));

		//first camera
		cameraObject->setPosition(vec3(0.0f, 20.0f, 15.0f), LOCAL);
		cameraObject->setRotation(glm::rotate(-PI/4, UNIT_X_V3), LOCAL);

	}; // end loadScene

	virtual void processGameInput() override
	{
		// Call the super class method
		Game::processGameInput();
	}


};
