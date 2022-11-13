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
		//sphereMat.diffuseMat = BLUE_RGBA;

		//create texture object                              
		sphereMat.setDiffuseTexture(Texture::GetTexture("Textures/sun.jpg")->getTextureObject());
		sphereMat.setTextureMode(DECAL);

		// Instantiate a box shaped mesh
		SphereMeshComponent* sphere = new SphereMeshComponent(shaderProgram, sphereMat, 3.0f);

		// Create a container to hold the box
		GameObject* firstGameObject = new GameObject(); 

		//Sound component for the sun
		SoundSourceComponent* spaceSound = new SoundSourceComponent("Sounds/Bohemian Rhapsody(Mercury).wav", 1.0f, 2.0f, 5.0f);
		spaceSound->play();
		spaceSound->setLooping(true);
		spaceSound->setGain(1.5f);
		//->setReferenceDistance(0.0f);
		//spaceSound->setMaxDistance(1.0f);

		// Add the box to a GameObject
		firstGameObject->addComponent(sphere); 
		//firstGameObject->addComponent(new SpinComponent(20.0f, UNIT_Y_V3, 100));
		firstGameObject->addComponent(spaceSound);

		////Add a car
		GameObject* secondGameObject = new GameObject();

		SoundListenerComponent* soundListener = new SoundListenerComponent();

		//secondGameObject->addComponent(new ModelMeshComponent("my_objects/car.obj", shaderProgram));
		secondGameObject->setScale(vec3(0.1f, 0.1f, 0.1f), LOCAL);
		secondGameObject->addComponent(new ModelMeshComponent("jet_models/F-15C_Eagle.obj", shaderProgram));
		secondGameObject->addComponent(new TranslateComponent(vec3(-3.0f, 0.0f, -4.0f)));
		secondGameObject->addComponent(new SteerComponent(60.0f));
		secondGameObject->addComponent(soundListener);
	
		////third game object - earth
		GameObject* earthGameObject = new GameObject();
		
		Material earthMat;
		//earthMat.diffuseMat = BLUE_RGBA;

		//create texture object                              
		earthMat.setDiffuseTexture(Texture::GetTexture("Textures/earth.jpg")->getTextureObject());

		//earth sound 
		SoundSourceComponent* earthSound = new SoundSourceComponent("Sounds/sweet-child-o-mine.wav", 1.0f, 2.0f, 5.0f);
		earthSound->play();
		earthSound->setLooping(true);
		earthSound->setGain(0.3f);
		//earthSound->setMaxDistance(1.0f);

		// Instantiate a box shaped mesh
		SphereMeshComponent* earth = new SphereMeshComponent(shaderProgram, earthMat, 1.0f);

		earthGameObject->addComponent(earth);
		earthGameObject->addComponent(earthSound);

		//********************************************
		GameObject* moonGameObject = new GameObject();

		Material moonMat;
		//moonMat.diffuseMat = BLUE_RGBA;

		//create texture object                              
		moonMat.setDiffuseTexture(Texture::GetTexture("Textures/moon.jpg")->getTextureObject());

		// Instantiate a box shaped mesh
		SphereMeshComponent* moon = new SphereMeshComponent(shaderProgram, moonMat, 0.25f);

		moonGameObject->addComponent(moon);
		

		//********************************************

		GameObject* earthSpinGameObject = new GameObject();
		earthSpinGameObject->addComponent(new SpinComponent(20.0f, UNIT_Y_V3, 100));
		
		earthGameObject->addComponent(new SpinComponent(100.0f));

		GameObject* earthLocationGameObject = new GameObject();
		earthLocationGameObject->setPosition(vec3(15.0f, 0.0f, 0.0f), LOCAL);


		GameObject* moonSpinGameObject = new GameObject();
		moonSpinGameObject->addComponent(new SpinComponent(300.0f, UNIT_Y_V3, 100));

		moonGameObject->setPosition(vec3(2.0f, 0.0f, 0.0f), LOCAL);

		moonGameObject->addComponent(new SpinComponent(1000.0f));

		firstGameObject->addChildGameObject(earthSpinGameObject);
		earthSpinGameObject->addChildGameObject(earthLocationGameObject);
		earthLocationGameObject->addChildGameObject(earthGameObject);
		earthLocationGameObject->addChildGameObject(moonSpinGameObject);
		moonSpinGameObject->addChildGameObject(moonGameObject);

		/*******************Mars*************************/

		////fourth game object - mars
		GameObject* marsGameObject = new GameObject();

		Material marsMat;
		//marsMat.diffuseMat = BLUE_RGBA;

		//create texture object                              
		marsMat.setDiffuseTexture(Texture::GetTexture("Textures/mars.jpg")->getTextureObject());

		//mars sound 
		SoundSourceComponent* marsSound = new SoundSourceComponent("Sounds/21 Guns.wav", 1.0f, 2.0f, 5.0f);
		marsSound->play();
		marsSound->setLooping(true);
		marsSound->setGain(0.8f);

		// Instantiate a box shaped mesh
		SphereMeshComponent* mars = new SphereMeshComponent(shaderProgram, marsMat, 0.8f);

		marsGameObject->addComponent(mars);
		marsGameObject->addComponent(marsSound);

		//********************************************
		GameObject* moonMarsGameObject = new GameObject();
		GameObject* secondMoonMarsGameObject = new GameObject();

		//create first moon mesh and add it
		Material moonMarsMat;
		//moonMarsMat.diffuseMat = BLUE_RGBA;                             
		moonMarsMat.setDiffuseTexture(Texture::GetTexture("Textures/moon.jpg")->getTextureObject());
		SphereMeshComponent* moonMars = new SphereMeshComponent(shaderProgram, moonMarsMat, 0.2f);
		moonMarsGameObject->addComponent(moonMars);

		//create second moon mesh and add it
		Material secondMoonMarsMat;
		//secondMoonMarsMat.diffuseMat = BLUE_RGBA;
		secondMoonMarsMat.setDiffuseTexture(Texture::GetTexture("Textures/moon.jpg")->getTextureObject());
		SphereMeshComponent* secondMoonMars = new SphereMeshComponent(shaderProgram, secondMoonMarsMat, 0.3f);
		secondMoonMarsGameObject->addComponent(secondMoonMars);

		//********************************************

		GameObject* marsSpinGameObject = new GameObject();
		marsSpinGameObject->addComponent(new SpinComponent(12.0f, UNIT_Y_V3, 100));
		
		marsGameObject->addComponent(new SpinComponent(100.0f));

		GameObject* marsLocationGameObject = new GameObject();
		marsLocationGameObject->setPosition(vec3(25.0f, 0.0f, 0.0f), LOCAL);

		GameObject* moonMarsSpinGameObject = new GameObject();
		GameObject* secondMoonMarsSpinGameObject = new GameObject();

		moonMarsSpinGameObject->addComponent(new SpinComponent(100.0f, UNIT_Y_V3, 100));
		secondMoonMarsSpinGameObject->addComponent(new SpinComponent(200.0f, UNIT_Y_V3, 100));

		moonMarsGameObject->setPosition(vec3(2.0f, 0.0f, 0.0f), LOCAL);
		secondMoonMarsGameObject->setPosition(vec3(3.0f, 0.0f, 0.0f), LOCAL);

		moonMarsGameObject->addComponent(new SpinComponent(-500.0f));
		secondMoonMarsGameObject->addComponent(new SpinComponent(-1000.0f));

		firstGameObject->addChildGameObject(marsSpinGameObject);
		marsSpinGameObject->addChildGameObject(marsLocationGameObject);
		marsLocationGameObject->addChildGameObject(marsGameObject);

		//first mars moon
		marsLocationGameObject->addChildGameObject(moonMarsSpinGameObject);
		moonMarsSpinGameObject->addChildGameObject(moonMarsGameObject);

		//second mars moon
		marsLocationGameObject->addChildGameObject(secondMoonMarsSpinGameObject);
		secondMoonMarsSpinGameObject->addChildGameObject(secondMoonMarsGameObject);

		/******************Jupiter****************************/
		////fifth game object - jupiter
		GameObject* jupiterGameObject = new GameObject();

		Material jupiterMat;
		//jupiterMat.diffuseMat = BLUE_RGBA;

		//create texture object                              
		jupiterMat.setDiffuseTexture(Texture::GetTexture("Textures/jupiter.jpg")->getTextureObject());

		//earth sound 
		SoundSourceComponent* jupiterSound = new SoundSourceComponent("Sounds/love-of-my-life.wav", 1.0f, 2.0f, 5.0f);
		jupiterSound->play();
		jupiterSound->setLooping(true);
		jupiterSound->setGain(1.0f);

		// Instantiate a box shaped mesh
		SphereMeshComponent* jupiter = new SphereMeshComponent(shaderProgram, jupiterMat, 2.0f);

		jupiterGameObject->addComponent(jupiter);
		jupiterGameObject->addComponent(jupiterSound);

		//********************************************

		GameObject* jupiterSpinGameObject = new GameObject();
		jupiterSpinGameObject->addComponent(new SpinComponent(9.0f, UNIT_Y_V3, 100));

		jupiterGameObject->addComponent(new SpinComponent(80.0f));

		GameObject* jupiterLocationGameObject = new GameObject();
		jupiterLocationGameObject->setPosition(vec3(35.0f, 0.0f, 0.0f), LOCAL);


		firstGameObject->addChildGameObject(jupiterSpinGameObject);
		jupiterSpinGameObject->addChildGameObject(jupiterLocationGameObject);
		jupiterLocationGameObject->addChildGameObject(jupiterGameObject);

		/*******************************Solar Traveling*****************************************/

		std::vector<GameObject*> planets;
		planets.push_back(firstGameObject);
		planets.push_back(earthGameObject);
		planets.push_back(marsGameObject);
		planets.push_back(jupiterGameObject);

		secondGameObject->addComponent(new SolarTravelComponent(planets, vec3(10.0f, 0.0f, 0.0f)));

		/*****************************************************************************/

		//Create camera object
		GameObject* cameraObject = new GameObject();
		CameraComponent* firstCamera = new CameraComponent(0, 60.0);
		firstCamera->setViewPort(0.0f, 0.0f, 1.0f, 0.5f);
		//firstCamera->setCameraClearColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));

		GameObject* secondCameraObject = new GameObject();
		CameraComponent* secondCamera = new CameraComponent(1, 60.0);
		secondCamera->setViewPort(0.0f, 0.5f, 1.0f, 0.5f);
		
		//set the clear color for the camera to be black
		secondCamera->setCameraClearColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));
		firstCamera->setCameraClearColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));

		//Add component to object
		cameraObject->addComponent(firstCamera);
		//cameraObject->addComponent(new ArrowRotateComponent());
		secondCameraObject->addComponent(secondCamera);
		
		//Create a game object to hold the light
		GameObject* PoslightObject = new GameObject();

		GameObject* SpotlightObject = new GameObject();

		//A directional light
		//LightComponent* dir = new DirectionalLightComponent(GLFW_KEY_D);
		//dir->setAmbientColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		//A positional light 
		PositionalLightComponent* pos = new PositionalLightComponent(GLFW_KEY_P);
		pos->setAmbientColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		pos->setEnable(true);

		//for shining globes, set diffuse color
		//pos->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		//A spot light
		SpotLightComponent* spot = new SpotLightComponent(GLFW_KEY_S);
		spot->setAmbientColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));
		spot->setCutoffAngleInDegrees(20.0f);
		spot->setEnable(true);

		SpotlightObject->addComponent(spot);
		
		SpotlightObject->setPosition(vec3(0.0f, 0.0f, 0.0f), LOCAL);
		
		secondGameObject->addChildGameObject(SpotlightObject);

		//Add component back to the game object
		
		PoslightObject->addComponent(pos);
		firstGameObject->addChildGameObject(PoslightObject);
		//lightObject->addComponent(spot);

		// Add the game object to the game
		this->addChildGameObject(firstGameObject);
		this->addChildGameObject(secondGameObject);
		//this->addChildGameObject(thirdGameObject);
		//this->addChildGameObject(lightObject);

		secondGameObject->addChildGameObject(cameraObject);
		//this->addChildGameObject(cameraObject);

		this->addChildGameObject(secondCameraObject);
		

		//secondGameObject->addChildGameObject(cameraObject);

		// Rotate the box game object that contains the cube
		//firstGameObject->setRotation(glm::rotate(PI / 4.0f, UNIT_Y_V3)); //******************* Week 8 ********************
		//secondGameObject->setPosition(vec3(3.0f, 1.0f, 1.0f));
		//thirdGameObject->setPosition(vec3(0.0f, 0.0f, 0.0f));
		
		//Spawn the spaceship
		/*secondGameObject->setPosition(vec3(100.0f, 0.0f, 1.0f), WORLD);*/
		 
		//second camera 
		cameraObject->setPosition(vec3(0.0f, 3.0f, 5.0f), LOCAL);
		cameraObject->setRotation(glm::rotate(-PI/9, UNIT_X_V3));

		//first camera
		secondCameraObject->setPosition(vec3(0.0f, 70.0f, 0.0f), LOCAL);
		secondCameraObject->setRotation(glm::rotate(-PI / 2, UNIT_X_V3));
		//cameraObject->setRotation(glm::rotate(-PI/2, UNIT_X_V3), LOCAL);

		//reparenting moons
		moonSpinGameObject->addComponent(new ReparentComponent(secondGameObject, 7.0f));
		moonMarsSpinGameObject->addComponent(new ReparentComponent(secondGameObject, 7.0f));
		secondMoonMarsSpinGameObject->addComponent(new ReparentComponent(secondGameObject, 7.0f));

	}; // end loadScene

	virtual void processGameInput() override
	{
		// Call the super class method
		Game::processGameInput();
	}


};
