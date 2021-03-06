
#include "Application.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "Scene01.h"
#include "Scene02.h"
#include "Scene03.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneMenu.h"
#include "SceneRanking.h"
#include "score.h"
#include "SceneEnd.h"
#include "Guide.h"

const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

GLFWwindow* Application::m_window = 0;

SceneManager *SceneManager::instance = 0;
std::vector<Scene*> SceneManager::scenevec;
int SceneManager::currSceneID = 0;
int SceneManager::nextSceneID = 0;
StopWatch Application::m_timer;
bool Application::exitProg = false;
int Application::sizeX = 800;
int Application::sizeY = 600;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}
void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
	Application::sizeX = w;
	Application::sizeY = h;
}
int Application::getWindowSizeX()
{
	return Application::sizeX;
}
int Application::getWindowSizeY()
{
	return Application::sizeY;
}
void Application::Init()
{

	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(Application::getWindowSizeX(), Application::getWindowSizeY(), "Computer Graphics", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowSizeCallback(m_window, resize_callback);
	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	//Main Loop
	Scene *scene0 = new SceneMenu();
	Scene *scene1 = new Scene01();
	Scene *scene2 = new Scene02();
	Scene *scene3 = new Scene03();
	Scene *scene4 = new SceneLoading();
	Scene *scene5 = new SceneRanking();
	Scene *scene6 = new SceneEnd();
	Scene *scene7 = new Guide();

	scene0->Init();

	SceneManager::getInstance()->AddScene(scene0);
	SceneManager::getInstance()->AddScene(scene1);
	SceneManager::getInstance()->AddScene(scene2);
	SceneManager::getInstance()->AddScene(scene3);
	SceneManager::getInstance()->AddScene(scene4);
	SceneManager::getInstance()->AddScene(scene5);
	SceneManager::getInstance()->AddScene(scene6);
	SceneManager::getInstance()->AddScene(scene7);

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE) && !exitProg)
	{
		SceneManager::getInstance()->Update();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	SceneManager::getInstance()->~SceneManager();
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
