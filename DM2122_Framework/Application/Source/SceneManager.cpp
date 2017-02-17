#include "SceneManager.h"

SceneManager::SceneManager()
{
	currSceneID = nextSceneID = 0;
}
void SceneManager::initAllScene()
{
	for (unsigned int i = 0; i < scenevec.size(); i++)
	{
		scenevec[i]->Init();
	}
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
	nextSceneID = sceneID;
	currSceneID = nextSceneID;
	scenevec.at(currSceneID)->Init();
}
Scene* SceneManager::getCurrentScene()
{
	return scenevec.at(currSceneID);
}
void SceneManager::Update()
{
	scenevec.at(currSceneID)->Update(Application::m_timer.getElapsedTime());
	scenevec.at(currSceneID)->Render();
}