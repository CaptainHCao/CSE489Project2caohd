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
		GameObject* sunGameObject = new GameObject(); 
		//Sound component for the sun
		SoundSourceComponent* spaceSound = new SoundSourceComponent("Sounds/Bohemian Rhapsody(Mercury).wav", 1.0f, 2.0f, 5.0f);
		spaceSound->play();
		spaceSound->setLooping(true);
		spaceSound->setGain(1.5f);
		//->setReferenceDistance(0.0f);
		//spaceSound->setMaxDistance(1.0f);

		// Add the box to a GameObject
		sunGameObject->addComponent(sphere); 
		//sunGameObject->addComponent(new SpinComponent(20.0f, UNIT_Y_V3, 100));
		sunGameObject->addComponent(spaceSound);

		//Add a space ship
		GameObject* spaceShipGameObject = new GameObject();

		//Add sound listener to the spaceship
		SoundListenerComponent* soundListener = new SoundListenerComponent();

		//set spaceship's model, scale, sound listener and steering component
		spaceShipGameObject->setScale(vec3(0.001f, 0.001f, 0.001f), LOCAL);
		spaceShipGameObject->addComponent(new ModelMeshComponent("my_objects/SciFi_Fighter_AK5.obj", shaderProgram));
		spaceShipGameObject->addComponent(new TranslateComponent(vec3(-3.0f, 0.0f, -4.0f)));
		spaceShipGameObject->addComponent(new SteerComponent(60.0f));
		spaceShipGameObject->addComponent(soundListener);
	
		//earth game object
		GameObject* earthGameObject = new GameObject();
		
		Material earthMat;

		//create texture object                              
		earthMat.setDiffuseTexture(Texture::GetTexture("Textures/earth.jpg")->getTextureObject());

		//earth sound 
		SoundSourceComponent* earthSound = new SoundSourceComponent("Sounds/sweet-child-o-mine.wav", 1.0f, 2.0f, 5.0f);
		earthSound->play();
		earthSound->setLooping(true);
		earthSound->setGain(0.3f);

		// Instantiate earth mesh
		SphereMeshComponent* earth = new SphereMeshComponent(shaderProgram, earthMat, 1.0f);

		//add earth mesh and earth sound
		earthGameObject->addComponent(earth);
		earthGameObject->addComponent(earthSound);

		//**************** Earth's Moon ********************
		GameObject* moonGameObject = new GameObject();

		Material moonMat;

		//create texture object for moon                            
		moonMat.setDiffuseTexture(Texture::GetTexture("Textures/moon.jpg")->getTextureObject());

		// Instantiate moon mesh
		SphereMeshComponent* moon = new SphereMeshComponent(shaderProgram, moonMat, 0.25f);

		//add moon mesh to the game object
		moonGameObject->addComponent(moon);
		

		//***************** Place holder for earth to spin around the sun ******************

		GameObject* earthSpinGameObject = new GameObject();
		earthSpinGameObject->addComponent(new SpinComponent(20.0f, UNIT_Y_V3, 100));
		
		//earth spin speed around itself
		earthGameObject->addComponent(new SpinComponent(100.0f));

		//Place holder for the moon, translate the earth
		GameObject* earthLocationGameObject = new GameObject();
		earthLocationGameObject->setPosition(vec3(15.0f, 0.0f, 0.0f), LOCAL);

		//place holder for the moon to spin around the earth
		GameObject* moonSpinGameObject = new GameObject();
		moonSpinGameObject->addComponent(new SpinComponent(300.0f, UNIT_Y_V3, 100));

		//translate the moon
		moonGameObject->setPosition(vec3(2.0f, 0.0f, 0.0f), LOCAL);

		//set the speed of spinning
		moonGameObject->addComponent(new SpinComponent(1000.0f));

		//Setting the logic for the scene graph nodes
		sunGameObject->addChildGameObject(earthSpinGameObject);
		earthSpinGameObject->addChildGameObject(earthLocationGameObject);
		earthLocationGameObject->addChildGameObject(earthGameObject);
		earthLocationGameObject->addChildGameObject(moonSpinGameObject);
		moonSpinGameObject->addChildGameObject(moonGameObject);

		/*******************Mars*************************/

		///mars game object
		GameObject* marsGameObject = new GameObject();

		Material marsMat;

		//create texture object for mars                          
		marsMat.setDiffuseTexture(Texture::GetTexture("Textures/mars.jpg")->getTextureObject());

		//mars sound 
		SoundSourceComponent* marsSound = new SoundSourceComponent("Sounds/21 Guns.wav", 1.0f, 2.0f, 5.0f);
		marsSound->play();
		marsSound->setLooping(true);
		marsSound->setGain(0.8f);

		// Instantiate mars mesh
		SphereMeshComponent* mars = new SphereMeshComponent(shaderProgram, marsMat, 0.8f);

		//add mesh and sound to mars game object
		marsGameObject->addComponent(mars);
		marsGameObject->addComponent(marsSound);

		//************** Mar's moons ****************

		//the moons' game objects
		GameObject* moonMarsGameObject = new GameObject();
		GameObject* secondMoonMarsGameObject = new GameObject();

		//create first moon mesh and add it to the game object
		Material moonMarsMat;                            
		moonMarsMat.setDiffuseTexture(Texture::GetTexture("Textures/moon.jpg")->getTextureObject());
		SphereMeshComponent* moonMars = new SphereMeshComponent(shaderProgram, moonMarsMat, 0.2f);
		moonMarsGameObject->addComponent(moonMars);

		//create second moon mesh and add it to the game object
		Material secondMoonMarsMat;
		secondMoonMarsMat.setDiffuseTexture(Texture::GetTexture("Textures/moon.jpg")->getTextureObject());
		SphereMeshComponent* secondMoonMars = new SphereMeshComponent(shaderProgram, secondMoonMarsMat, 0.3f);
		secondMoonMarsGameObject->addComponent(secondMoonMars);

		//********************* Mars ***********************

		//Place holdear for the mars to spin around the sun
		GameObject* marsSpinGameObject = new GameObject();
		marsSpinGameObject->addComponent(new SpinComponent(12.0f, UNIT_Y_V3, 100));
		
		//set the mars spinning speed
		marsGameObject->addComponent(new SpinComponent(100.0f));

		//placeholder for the moons location
		GameObject* marsLocationGameObject = new GameObject();

		//translate the mars
		marsLocationGameObject->setPosition(vec3(25.0f, 0.0f, 0.0f), LOCAL);

		//Placeholder for moons to spin around the mars
		GameObject* moonMarsSpinGameObject = new GameObject();
		GameObject* secondMoonMarsSpinGameObject = new GameObject();

		//add the spinning components
		moonMarsSpinGameObject->addComponent(new SpinComponent(100.0f, UNIT_Y_V3, 100));
		secondMoonMarsSpinGameObject->addComponent(new SpinComponent(200.0f, UNIT_Y_V3, 100));

		//translate the radius of spinning
		moonMarsGameObject->setPosition(vec3(2.0f, 0.0f, 0.0f), LOCAL);
		secondMoonMarsGameObject->setPosition(vec3(3.0f, 0.0f, 0.0f), LOCAL);

		//set the speeds of spinning for the moons
		moonMarsGameObject->addComponent(new SpinComponent(-500.0f));
		secondMoonMarsGameObject->addComponent(new SpinComponent(-1000.0f));

		//setting the logic for the scene graph nodes 
		sunGameObject->addChildGameObject(marsSpinGameObject);
		marsSpinGameObject->addChildGameObject(marsLocationGameObject);
		marsLocationGameObject->addChildGameObject(marsGameObject);

		//first mars moon
		marsLocationGameObject->addChildGameObject(moonMarsSpinGameObject);
		moonMarsSpinGameObject->addChildGameObject(moonMarsGameObject);

		//second mars moon
		marsLocationGameObject->addChildGameObject(secondMoonMarsSpinGameObject);
		secondMoonMarsSpinGameObject->addChildGameObject(secondMoonMarsGameObject);

		/******************Jupiter****************************/
		//jupiter game object
		GameObject* jupiterGameObject = new GameObject();

		Material jupiterMat;

		//create texture object for the jupiter                             
		jupiterMat.setDiffuseTexture(Texture::GetTexture("Textures/jupiter.jpg")->getTextureObject());

		//jupiter sound
		SoundSourceComponent* jupiterSound = new SoundSourceComponent("Sounds/love-of-my-life.wav", 1.0f, 2.0f, 5.0f);
		jupiterSound->play();
		jupiterSound->setLooping(true);
		jupiterSound->setGain(1.0f);

		// Instantiate jupiter mesh
		SphereMeshComponent* jupiter = new SphereMeshComponent(shaderProgram, jupiterMat, 2.0f);

		//add mesh and sound to the game object
		jupiterGameObject->addComponent(jupiter);
		jupiterGameObject->addComponent(jupiterSound);

		//*****************Jupiter********************

		//Placeholder for jupiter to spin around the sun
		GameObject* jupiterSpinGameObject = new GameObject();
		jupiterSpinGameObject->addComponent(new SpinComponent(9.0f, UNIT_Y_V3, 100));

		//set the spinning speed
		jupiterGameObject->addComponent(new SpinComponent(80.0f));

		//placeholder to translate the jupiter (set the radius to spin around the sun)
		GameObject* jupiterLocationGameObject = new GameObject();
		jupiterLocationGameObject->setPosition(vec3(35.0f, 0.0f, 0.0f), LOCAL);

		//setting the logic for the scene graph nodes
		sunGameObject->addChildGameObject(jupiterSpinGameObject);
		jupiterSpinGameObject->addChildGameObject(jupiterLocationGameObject);
		jupiterLocationGameObject->addChildGameObject(jupiterGameObject);

		/*******************************Solar Traveling*****************************************/

		std::vector<GameObject*> planets;
		planets.push_back(sunGameObject);
		planets.push_back(earthGameObject);
		planets.push_back(marsGameObject);
		planets.push_back(jupiterGameObject);

		spaceShipGameObject->addComponent(new SolarTravelComponent(planets, vec3(10.0f, 0.0f, 0.0f)));

		/*****************************************************************************/

		//Create camera object
		GameObject* cameraObject = new GameObject();
		CameraComponent* firstCamera = new CameraComponent(0, 60.0);

		//bottom camera
		firstCamera->setViewPort(0.0f, 0.0f, 1.0f, 0.5f);

		//create second camera object
		GameObject* secondCameraObject = new GameObject();
		CameraComponent* secondCamera = new CameraComponent(1, 60.0);

		//above camera
		secondCamera->setViewPort(0.0f, 0.5f, 1.0f, 0.5f);
		
		//set the clear color for the camera to be black
		secondCamera->setCameraClearColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));
		firstCamera->setCameraClearColor(vec4(0.0f, 0.0f, 0.0f, 1.0f));

		//Add first camera component to first camera object
		cameraObject->addComponent(firstCamera);
		
		//Add second camera component to second camera object
		secondCameraObject->addComponent(secondCamera);
		
		//Create a game objects to hold the light
		GameObject* PoslightObject = new GameObject();
		GameObject* SpotlightObject = new GameObject();

		//A directional light
		//LightComponent* dir = new DirectionalLightComponent(GLFW_KEY_D);
		//dir->setAmbientColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		//A positional light 
		PositionalLightComponent* pos = new PositionalLightComponent(GLFW_KEY_P);
		pos->setAmbientColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		pos->setEnable(true);
		PoslightObject->addComponent(pos);
		//add the positional light to the sun
		sunGameObject->addChildGameObject(PoslightObject);

		//for shining globes, set diffuse color
		//pos->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		//A spot light
		SpotLightComponent* spot = new SpotLightComponent(GLFW_KEY_S);
		spot->setAmbientColor(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));
		spot->setCutoffAngleInDegrees(20.0f);
		spot->setEnable(true);
		SpotlightObject->addComponent(spot);	
		SpotlightObject->setPosition(vec3(0.0f, 0.0f, 0.0f), LOCAL);
		//add spotlight to be the spaceship's headlight
		spaceShipGameObject->addChildGameObject(SpotlightObject);

		// Add the game object to the game
		this->addChildGameObject(sunGameObject);
		this->addChildGameObject(spaceShipGameObject);

		//first camera attached to the spaceship
		spaceShipGameObject->addChildGameObject(cameraObject);

		//second camera attached to the game
		this->addChildGameObject(secondCameraObject);
		
		//Spawn the spaceship
		/*spaceShipGameObject->setPosition(vec3(100.0f, 0.0f, 1.0f), WORLD);*/
		 
		//first camera set to be right behind, and above the spaceship
		cameraObject->setPosition(vec3(0.0f, 3.0f, 5.0f), LOCAL);
		cameraObject->setRotation(glm::rotate(-PI/9, UNIT_X_V3));

		//second camera set to be looking at the solar system from above
		secondCameraObject->setPosition(vec3(0.0f, 70.0f, 0.0f), LOCAL);
		secondCameraObject->setRotation(glm::rotate(-PI / 2, UNIT_X_V3));

		//reparenting moons
		moonSpinGameObject->addComponent(new ReparentComponent(spaceShipGameObject, 7.0f));
		moonMarsSpinGameObject->addComponent(new ReparentComponent(spaceShipGameObject, 7.0f));
		secondMoonMarsSpinGameObject->addComponent(new ReparentComponent(spaceShipGameObject, 7.0f));

	}; // end loadScene

	virtual void processGameInput() override
	{
		// Call the super class method
		Game::processGameInput();
	}


};
