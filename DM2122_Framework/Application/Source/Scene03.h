#ifndef SCENE_03_H
#define SCENE_03_H

#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Player.h"
#include <string>
#include <vector>
using std::string;

class Scene03 : public Scene
{
public:
	Scene03();
	~Scene03();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle = 0;
	float translateX = 5;
	float scaleAll = 5;
	string FPS;

	int pi_tx = 70;
	int pi_ty = 41;

	// Enemy Container
	std::vector<Enemy> EnemyContainer;

	enum GEOMETRY_TYPE
	{
		PLAYER_ICON,
		OVERLAY,
		MAP,

		FLOOR_MODEL,
		HELIPAD_MODEL,
		HELICOPTER_MODEL,
		HELIBLADE_MODEL,
		PIPE_MODEL,
		NPC_ROBOT,
		RIGHT_DOOR,
		LEFT_DOOR,
		DIALOGUE,

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
		PLAYER_LASER,
		PLAYER_GUN,

		HEALTH,
		HEALTH_BAR,
		SHIELD,
		SHIELD_BAR,
		ABILITY,
		ABILITY_BAR,

		//============ Enemies Assests ================//
		ENEMY_01_BODY,
		ENEMY_01_WAIST,
		ENEMY_01_LEG,
		ENEMY_01_BULLET,

		ENEMY_02_BODY,
		ENEMY_02_LEFT_SHLDR,
		ENEMY_02_LEFT_ARM,
		ENEMY_02_LEFT_LEG,
		ENEMY_02_LEFT_KNEE,
		ENEMY_02_RIGHT_ARM,
		ENEMY_02_RIGHT_LEG,
		ENEMY_02_RIGHT_KNEE,
		//=============================================//

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
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey, int rotatez);
	void RenderMap();
	void RenderHelicopter();
	void RenderMinimap();
	void Interactible();
	GameObject MakeGameObject(Vector3 newPos, float newSizeX, float newSizeZ);

	// Player Components
	void RenderPlayer();
	void RenderPlayerUI();

	// Enemies Components
	void RenderEnemies();
	void RenderEnemyBullets();
	Enemy MakeEnemy(Vector3 newPos, float newSizeX = 1, float newSizeZ = 1, EnemyType ThisType = Ranged);
	void SpawnEnemy();

	Player player;

	float laserScale = 1;
	bool playerShot = false;

	float HeliBladeRotation = 0.0f;
	float RightDoorTranslate = 0.0f;
	float LeftDoorTranslate = 0.0f;

	bool Talkedto = false;
	bool TriggerDoorOpen = false;
	bool CloseRight = false;
	bool CloseLeft = false;
	bool SpawnRight = false;
	bool SpawnLeft = false;
	bool RightRoomDone = false;
	bool LeftRoomDone = false;
};

#endif