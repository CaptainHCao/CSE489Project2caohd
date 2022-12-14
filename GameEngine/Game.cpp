#include "GameEngine.h"
#include "SoundEngine.h"

#define VERBOSE false



//********************* Initialization Methods *****************************************


Game::Game(std::string windowTitle)
	: windowTitle(windowTitle)
{

} // end Game Constructor

void Game::runGame()
{
	// Set the owning game to this game. The will be passed to all
	// other GameObjects when addChildGameObject is called
	this->owningGame = this;

	// The Game is the root of the scene graph. It does not 
	// have a  parent.
	this->parent = nullptr;

	// Initialize the game
	bool success = initializeGame();

	// Enter the game loop
	if (success) {
		gameLoop();
	}

	// Free up resources
	shutdown();

} // end runGame

Game::~Game()
{
	if (VERBOSE) cout << "Game destructor " << endl;

	deleteAllChildren(); //******************* Week 8 ********************


} // end Game Destructor

bool Game::initializeGame()
{
	// Initialize the various libararies
	bool windowInit = initializeRenderWindow();
	bool graphicsInit = initializeGraphics();

	bool soundInit = SoundEngine::Init();

	// Check if all libraries initialized correctly
	if (windowInit && graphicsInit && soundInit)
	{
		// Set the owner of all the GameObject (temporary)
		GameObject::SetOwningGame(this);

		// Build the scene graph
		loadScene();

		// Explicitly call the resize method to set the initial projection transformation
		// and viewport based on framebuffer size.
		framebuffer_size_callback(this->renderWindow, initialScreenWidth, initialScreenHeight);

		// Initialize the scene graph
		this->initialize(); //******************* Week 8 ********************

		// Return true to indicate the game has initialized
		return true;
	}
	else
	{
		// Return false to indicate the game did not initialize correctly
		return false;
	}

} // end initialize

bool Game::initializeRenderWindow()
{
	// Initialize the GLFW window. If a failure, then exit
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// Specify that OpenGL will be the client API for the rendering context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	// Use the core OpenGL profile	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window in debug mode for additional error and diagnostic reporting 
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	// Flush the rendering pipeline when the context is released
	glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH);

	// Explicitly request double buffers i.e. two frame buffers
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	// Create rendering window and the OpenGL context.
	renderWindow = glfwCreateWindow(initialScreenWidth, initialScreenHeight, windowTitle.c_str(), NULL, NULL);

	if (!renderWindow) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(renderWindow);

	//  Ensure that glfwGetKey returns GLFW_PRESS the each time
	//  it is called even if the key had been released before the call
	glfwSetInputMode(renderWindow, GLFW_STICKY_KEYS, true);
	
	// Set the swap interval for the OpenGL context i.e. the number of screen 
	// updates to wait between before swapping the buffer and returning.
	glfwSwapInterval(1);

	// Bind all callback functions to handle window events
	bindCallBacks();

	if (VERBOSE) cout << "Render Window Initialized" << endl;

	return true;

} // end initializeRenderWindow

bool Game::initializeGraphics()
{
	// ****** Initialize GLEW *********

	// Prevent possible initialization error when using the core context
	glewExperimental = GL_TRUE;

	GLenum res = glewInit(); // Must be done after glut is initialized!

	if (res != GLEW_OK) {

		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return false;
	}

	// On some platforms, GLEW will emit a benign error code. So clear it.
	glGetError();

	// ********* Initialize OpenGL **************

	// Register OpenGL error callback to print error messages to the console
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(openglMessageCallback, 0);

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);

	// Cull back faces of polygons
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// Render "filled in" polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Set source and destination blending functions
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (VERBOSE) cout << "Graphics Initialized" << endl;

	// Display OpenGL context information (OpenGL and GLSL versions) on the
	// command console.
	if (VERBOSE) displayOpenGlInfo();

	return true;

} // end initializeGraphics

void Game::bindCallBacks()
{
	// Set this game as the user defined window associated with the 
	// rendering window.
	glfwSetWindowUserPointer(renderWindow, this);

	// Register window resize callback function
	glfwSetFramebufferSizeCallback(renderWindow, framebufferResizeCallback);

	// Register window close function
	glfwSetWindowCloseCallback(renderWindow, windowCloseCallback);

} // end bindCallBacks


//********************* Run Methods *****************************************

void Game::gameLoop()
{
	isRunning = true;

	while (isRunning) {

		processGameInput();
		updateGame();
		renderScene();
	}

	if (VERBOSE) cout << "Exited Game Loop" << endl;

} // end gameLoop

void Game::processGameInput()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE)) {

		isRunning = false;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) && WireFrame_KeyDown == false) {

		GLint mode;
		glGetIntegerv(GL_POLYGON_MODE, &mode);

		if (mode == GL_FILL) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		WireFrame_KeyDown = true;

	}
	else if (!glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W)) {
		WireFrame_KeyDown = false;
	}

	// Start an input traversal of all SceneGrapNode/GameObjects in the game
	GameObject::processInput();//******************* Week 8 ********************

	// Add pending, delete removed, and reparent
	GameObject::ManageGameObjectChanges();//******************* Week 8 ********************


} // end processInput

void Game::updateGame()
{
	// Compute delta time
	static double lastRenderTime = glfwGetTime(); // static initilization only occurs once
	double currentTime = glfwGetTime();
	float deltaTime = static_cast<float>(currentTime - lastRenderTime);

	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	if (deltaTime >= FRAME_INTERVAL) {

		GameTime::delta_Time = deltaTime;

		// Must be called in order for callback functions
		// to be called for registered events.
		glfwPollEvents();

		// Start an update traversal of all SceneGrapNode/GameObjects in the game
		this->update(deltaTime);

		// Add pending, delete removed, and reparent
		GameObject::ManageGameObjectChanges(); 

		//update soundengine
		SoundEngine::Update();

		// Update the last time the game was updated
		lastRenderTime = currentTime; 
	}

} // end updateGame()

void Game::renderScene()
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Loop through activeCameras
	for (auto& camera : CameraComponent::GetActiveCameras()) {

		camera->setCameraTransformations();

		// Render the Scene ...
		for (auto mesh : MeshComponent::GetMeshComponents()) {

			mesh->draw();
		}
	}


	// Render the Scene ...
	for (auto & mesh : MeshComponent::GetMeshComponents()) {

		mesh->draw();
	}

	// Swap the front and back buffers
	glfwSwapBuffers(renderWindow);

} // end renderScene

//********************* Shutdown Methods *****************************************

void Game::shutdown()
{
	// Destroy the window
	glfwDestroyWindow(renderWindow);

	// Frees other allocated resources
	glfwTerminate();

	// Delete all shader programs that have been created
	deleteAllShaderPrograms();

	//shutdown the soundengine
	SoundEngine::Stop();

} // end shutDown

//********************* Accessor Methods *****************************************

glm::ivec2 Game::getWindowDimensions()
{
	int width, height;
	glfwGetFramebufferSize(this->renderWindow, &width, &height);

	return glm::ivec2(width, height);

} // end getWindowDimensions

//********************* Event Handlers *****************************************

void Game::window_close_callback(GLFWwindow* window)
{
	// Stop the game loop
	this->isRunning = false;

} // end window_close_callback


void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// Set parameters for the window transformation ...
	glViewport(0, 0, width, height);

	// Set the projection transformation ...
	mat4 perspectProjection = glm::perspective(PI / 6.0f, (float)width / height, 1.0f, 1000.f);
	SharedTransformations::setProjectionMatrix(perspectProjection);

} // end framebuffer_size_callback

//********************* static function definitions *****************************************

void glfw_error_callback(int error, const char* description) {

	fprintf(stderr, "Error: %s\n", description);

} // end error_callback


void displayOpenGlInfo(void)
{
	// Display the company responsible for this GL implementation
	fprintf(stdout, "OpenGL INFO:\n\tOpenGL Implementor: %s\n",
		glGetString(GL_VENDOR));
	// Display the renderer/graphics card
	fprintf(stdout, "\tRenderer: %s\n", glGetString(GL_RENDERER));
	// Display the OpenGL version that is implemented
	fprintf(stdout, "\tOpenGL Version: %s\n", glGetString(GL_VERSION));
	// Display the GLSL version
	fprintf(stdout, "\tGLSL Version: %s\n\n",
		glGetString(GL_SHADING_LANGUAGE_VERSION));

} // end displayOpenGlInfo


void GLAPIENTRY openglMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	if (severity != 0x826B) {
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}

} // end MessageCallback

static void framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	Game* that = static_cast<Game*>(glfwGetWindowUserPointer(window));
	that->framebuffer_size_callback(window, width, height);
}

static void windowCloseCallback(GLFWwindow* window)
{
	Game* that = static_cast<Game*>(glfwGetWindowUserPointer(window));
	that->window_close_callback(window);
}


