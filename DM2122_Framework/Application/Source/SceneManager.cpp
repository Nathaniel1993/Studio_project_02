#include "SceneManager.h"
#include "Application.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

SceneManager::SceneManager()
{
	currSceneID = nextSceneID = 0;
}
SceneManager::~SceneManager()
{
	while (!scenevec.empty())
	{
		scenevec.pop_back();
	}
}
SceneManager* SceneManager::getInstance()
{
	if (!instance)
	{
		instance = new SceneManager;
		return instance;
	}
	else
	{
		return instance;
	}
}
void SceneManager::AddScene(Scene *scene)
{
	scenevec.push_back(scene);
}
void SceneManager::SetNextScene(int sceneID)
{
	scenevec.at(currSceneID)->Exit();
	scenevec.at(nextSceneID)->Init();
	currSceneID = sceneID;
}
Scene* SceneManager::getCurrentScene()
{
	return scenevec.at(currSceneID);
}
void SceneManager::Update()
{
	scenevec.at(currSceneID)->Update(Application::m_timer.getElapsedTime());
	if (currSceneID != nextSceneID)
	{
		scenevec.at(3)->Init();
		scenevec.at(3)->Render();
		glfwSwapBuffers(Application::m_window);
		SetNextScene(nextSceneID);
	}
	scenevec.at(currSceneID)->Render();
}