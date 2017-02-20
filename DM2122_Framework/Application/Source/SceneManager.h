#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "Application.h"
#include <vector>
using std::vector;

class SceneManager
{
private:
	SceneManager();
	friend class Scene;
	static SceneManager* instance;
	static int currSceneID;
	static int nextSceneID;
	static vector<Scene*> scenevec;

public:
	~SceneManager();
	static SceneManager* getInstance();
	void AddScene(Scene *scene);
	void SetNextScene(int sceneID);
	static void SetNextSceneID(int sceneID) { nextSceneID = sceneID; };
	static Scene* getCurrentScene();
	void Update();

};
#endif