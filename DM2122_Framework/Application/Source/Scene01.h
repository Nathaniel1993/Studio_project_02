#ifndef SCENE_01_H
#define SCENE_01_H

#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>


class Scene01 : public Scene
{
public:
	Scene01();
	~Scene01();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	float rotateAngle = 0; //rotate camera
	float translateX = 5;
	float scaleAll = 5;

	float rotateThis = 0.0f;
	
	//std::vector<Enemy> EnemyContainer;

	enum GEOMETRY_TYPE
	{
		GEO_TRIANGLE_1,
		GEO_AXES,
		GEO_SPHERE,

		GEO_BULLET,

		FLOOR_MODEL,
		BUILDINGS_MODEL,
		TALL_BUILDINGS_MODEL,
		WALL_MODEL,

		ENEMY_01_BODY,
		ENEMY_01_WAIST,
		ENEMY_01_LEG,

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

		HEALTH,
		HEALTH_BAR,
		SHIELD,
		SHIELD_BAR,
		ABILITY,
		ABILITY_BAR,

		CRATE_MODEL,
		KEY_MODEL,
		HEALTH_MODEL,
		POLICECAR_MODEL,
		
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
	Enemy currEnemy;
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	void RenderEnemies();

	//void CollisionCheck();
	Enemy MakeEnemy(Vector3 newPos, float newSizeX = 1, float newSizeZ = 1);

	Player player;
	
	bool detectPlayer = false;
	bool scanPlayer = true;
	bool minLimit = false;

	void RenderCrates();
	void RenderHealthPack();
	void RenderMap();
	void RenderPlayer();
	void RenderPlayerUI();

	

	//Bullets
	
	void RenderBullets();
	//void CreateBullet(Vector3 newPos, double _dt);
	//bool ReadyToFire = false;

	float Key_Rotation = 0.0f;
	float Health_Rotation = 0.0f;

	bool enableLight = true;
};

#endif