
#ifndef APPLICATION_H
#define APPLICATION_H

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

#include "timer.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static void ChangeScene(int sceneNo);
	static bool exitProg;
	static GLFWwindow* m_window;
	static StopWatch m_timer;
};

#endif