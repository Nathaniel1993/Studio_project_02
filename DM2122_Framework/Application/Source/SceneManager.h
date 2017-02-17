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
	static void initAllScene();
	static Scene* getCurrentScene();
	void AddScene(Scene *scene);
	void SetNextScene(int sceneID);
	void Update();

};
#endif