#include "GameTime.h"
#include <GLFW/glfw3.h>


float GameTime::delta_Time = 0.1f;
double GameTime::lastRenderTime = glfwGetTime(); 
double GameTime::currentTime;


void GameTime::Time_Update()
{
	static double currentTime = glfwGetTime();
	delta_Time = static_cast<float>(currentTime - lastRenderTime);

}