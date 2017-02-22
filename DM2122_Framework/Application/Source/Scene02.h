#ifndef SCENE_02_H
#define SCENE_02_H

#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

#include <string>

using std::string;


class Scene02 : public Scene
{
public:
	Scene02();
	~Scene02();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle = 0;
	float translateX = 5;
	float scaleAll = 5;
	float subdoor_Translate = 0.0f;
	float maindoor_Translate = 0.0f;

	string buttonQuest;
	string switchQuest;
	string lightswitchQuest;
	string X_target;
	string Z_target;
	
	int buttonPressed = 0;
	int buttonPressed2 = 0;
	int switchPressed = 0;
	int switchPressed2 = 0;

	bool pressButton = false;
	bool pressButton2 = false;
	bool pressSwitch = false;
	bool pressSwitch2 = false;

	bool rightPos = false;
	bool rightPos1 = false;
	bool rightPos2 = false;
	bool rightPos3 = false;
	
	bool questOpen = false;
	bool questOpen1 = false;
	bool questOpen2 = false;
	bool subDoorOpen = false;
	bool mainDoorOpen = false;
	bool lightsOn = false;

	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1,
		GEO_AXES,
		GEO_QUAD,

		BOOKS_MODEL,
		DESKS_MODEL,
		FLOOR_MODEL,
		BUTTON_MODEL,
		NPC_MODEL,
		SOFA_MODEL,
		STAIRS_MODEL,
		SWITCHES_MODEL,
		WALL_MODEL,
		SUB_DOOR_MODEL,
		MAIN_DOOR_MODEL,

		PLAYER_BODY,
		RIGHT_SHOULDER,
		RIGHT_ARM,
		RIGHT_HAND,
		LEFT_SHOULDER,
		LEFT_ARM,
		LEFT_HAND,
		RIGHT_LEG,
		RIGHT_KNEE,
		LEFT_LEG,
		LEFT_KNEE,
		PLAYER_SWORD,
		PLAYER_GUN,

		GEO_TEXT,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};



private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_indexBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Mesh *meshList[NUM_GEOMETRY];
	Light light[1];
	Camera3 camera;
	MS modelStack, viewStack, projectionStack;
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	void RenderMap();
	void Interactible();
	void RenderPlayer();

	bool enableLight = true;
};

#endif