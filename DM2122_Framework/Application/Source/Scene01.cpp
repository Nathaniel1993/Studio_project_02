#include "Scene01.h"
#include "Application.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include "shader.hpp"
#include "Utility.h"
#include "LoadTGA.h"
#include "SceneManager.h"

Scene01::Scene01()
{
}

Scene01::~Scene01()
{
}

void Scene01::Init()
{
	EnemyContainer.push_back(MakeEnemy(Vector3(-100, 0, -100), 1, 1, Ranged));
	EnemyContainer.push_back(MakeEnemy(Vector3(0, 0, 0), 1, 1, Ranged));
	EnemyContainer.push_back(MakeEnemy(Vector3(100, 0, 100), 1, 1, Ranged));
	EnemyContainer.push_back(MakeEnemy(Vector3(200, 0, 0), 1, 1, Melee));
	EnemyContainer.push_back(MakeEnemy(Vector3(0, 0, 200), 1, 1, Melee));
	EnemyContainer.push_back(MakeEnemy(Vector3(-400, 0, -300), 1, 1, Melee));
	EnemyContainer.push_back(MakeEnemy(Vector3(700, 0, 700), 1, 1, Melee));

	//======================= Building Collision: ============================//
	BuildingContainer.push_back(MakeGameObject(Vector3(195, 0, 240), 99.0f, 86.f));
	BuildingContainer.push_back(MakeGameObject(Vector3(482, 0, 249), 93.0f, 270.f));
	BuildingContainer.push_back(MakeGameObject(Vector3(474, 0, -431), 95.0f, 80.f));
	BuildingContainer.push_back(MakeGameObject(Vector3(294, 0, -349), 54.0f, 231.f));
	BuildingContainer.push_back(MakeGameObject(Vector3(-344, 0, -311), 178.0f, 255.f));
	BuildingContainer.push_back(MakeGameObject(Vector3(-119, 0, 290), 164.0f, 131.5f));
	BuildingContainer.push_back(MakeGameObject(Vector3(29, 0, 11.5), 197.0f, 83.5f));
	BuildingContainer.push_back(MakeGameObject(Vector3(-92, 0, -135), 81.0f, 98.5f));
	BuildingContainer.push_back(MakeGameObject(Vector3(-351, 0, 197.5), 88.0f, 165.5f));
	BuildingContainer.push_back(MakeGameObject(Vector3(46.5, 0, -386.5), 147.5f, 95.5f));
	BuildingContainer.push_back(MakeGameObject(Vector3(30.5, 0, -520.5), 177.5f, 54.5f));
	//=========================================================================//

	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Set background colour to dark blue

	//glEnable(GL_CULL_FACE);

	//Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Generate buffers
	glGenBuffers(1, &m_vertexBuffer[0]);
	glGenBuffers(1, &m_indexBuffer[0]);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	//Enable Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Use our shader
	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	for (int i = 0; i < NUM_GEOMETRY; i++)
	{
		meshList[i] = NULL;
	}

	camera.Init(Vector3(650, 230, -150),
		Vector3(500, 0, -300),
		Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1.0f, 0.0f, 0.0f), 36, 36, 1.0f);
	meshList[GEO_BULLET] = MeshBuilder::GenerateSphere("sphere", Color(1.0f, 1.0f, 0.0f), 36, 36, 1.0f);

	//====================== Environment Assets ===================================

	meshList[FLOOR_MODEL] = MeshBuilder::GenerateOBJ("floor", "OBJ//Scene01//v2//floor.obj");
	meshList[FLOOR_MODEL]->textureID = LoadTGA("Image//Scene01//floor.tga");

	meshList[BUILDINGS_MODEL] = MeshBuilder::GenerateOBJ("buildings", "OBJ//Scene01//v2//buildings.obj");
	meshList[BUILDINGS_MODEL]->textureID = LoadTGA("Image//Scene01//buildings.tga");

	meshList[TALL_BUILDINGS_MODEL] = MeshBuilder::GenerateOBJ("tall buildings", "OBJ//Scene01//v2//tall_buildings.obj");
	meshList[TALL_BUILDINGS_MODEL]->textureID = LoadTGA("Image//Scene01//tall_buildings.tga");

	meshList[WALL_MODEL] = MeshBuilder::GenerateOBJ("wall", "OBJ//Scene01//v2//wall.obj");
	
	//====================== UI Assets =============================================

	meshList[HEALTH] = MeshBuilder::GenerateQuad("Player health", Color(1.0f, 1.0f, 1.0f), 1.0f, 1.0f);
	meshList[HEALTH]->textureID = LoadTGA("Image//Player_Health.tga");

	meshList[HEALTH_BAR] = MeshBuilder::GenerateQuad("Player health", Color(1.0f, 1.0f, 1.0f), 1.0f, 1.0f);
	meshList[HEALTH_BAR]->textureID = LoadTGA("Image//Player_Bar.tga");

	meshList[SHIELD] = MeshBuilder::GenerateQuad("Player shield", Color(1.0f, 1.0f, 1.0f), 1.0f, 1.0f);
	meshList[SHIELD]->textureID = LoadTGA("Image//Player_Shield.tga");

	meshList[SHIELD_BAR] = MeshBuilder::GenerateQuad("Player shield", Color(1.0f, 1.0f, 1.0f), 1.0f, 1.0f);
	meshList[SHIELD_BAR]->textureID = LoadTGA("Image//Player_Bar.tga");

	meshList[ABILITY] = MeshBuilder::GenerateQuad("Ability bar", Color(1.0f, 1.0f, 1.0f), 1.0f, 1.0f);
	meshList[ABILITY]->textureID = LoadTGA("Image//Player_Ability.tga");

	meshList[ABILITY_BAR] = MeshBuilder::GenerateQuad("Ability bar", Color(1.0f, 1.0f, 1.0f), 1.0f, 1.0f);
	meshList[ABILITY_BAR]->textureID = LoadTGA("Image//Player_Bar.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//System.tga");

	//======================= Minimap ======================================================
	meshList[PLAYER_ICON] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[PLAYER_ICON]->textureID = LoadTGA("Image//Minimap//arrowhead.tga");

	meshList[OVERLAY] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[OVERLAY]->textureID = LoadTGA("Image//Minimap//overlay.tga");

	meshList[MAP] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[MAP]->textureID = LoadTGA("Image//Minimap//minimap.tga");

	//====================== Enemy 01 Assets =============================================
	meshList[ENEMY_01_BODY] = MeshBuilder::GenerateOBJ("Enemy body", "OBJ//Enemy_01_Body.obj");
	meshList[ENEMY_01_BODY]->textureID = LoadTGA("Image//Enemy_01.tga");

	meshList[ENEMY_01_WAIST] = MeshBuilder::GenerateOBJ("Enemy waist", "OBJ//Enemy_01_Waist.obj");
	meshList[ENEMY_01_WAIST]->textureID = LoadTGA("Image//Enemy_01.tga");

	meshList[ENEMY_01_LEG] = MeshBuilder::GenerateOBJ("Enemy legs", "OBJ//Enemy_01_Leg.obj");
	meshList[ENEMY_01_LEG]->textureID = LoadTGA("Image//Enemy_01.tga");

	meshList[ENEMY_01_BULLET] = MeshBuilder::GenerateOBJ("bullet", "OBJ//Enemy_01_bullet.obj");
	meshList[ENEMY_01_BULLET]->textureID = LoadTGA("Image//bullet.tga");
	

	//====================== Enemy 02 Assets =============================================
	meshList[ENEMY_02_BODY] = MeshBuilder::GenerateOBJ("Enemy 2 body", "OBJ//Enemy02_Body.obj");
	meshList[ENEMY_02_BODY]->textureID = LoadTGA("Image//Enemy_02_UV.tga");

	meshList[ENEMY_02_LEFT_SHLDR] = MeshBuilder::GenerateOBJ("Enemy 2 left shoulder", "OBJ//Enemy02_left_shoulder.obj");
	meshList[ENEMY_02_LEFT_SHLDR]->textureID = LoadTGA("Image//Enemy_02_UV.tga");

	meshList[ENEMY_02_LEFT_ARM] = MeshBuilder::GenerateOBJ("Enemy 2 left arm", "OBJ//Enemy02_left_arm.obj");
	meshList[ENEMY_02_LEFT_ARM]->textureID = LoadTGA("Image//Enemy_02_UV.tga");

	meshList[ENEMY_02_LEFT_LEG] = MeshBuilder::GenerateOBJ("Enemy 2 left leg", "OBJ//Enemy02_left_leg.obj");
	meshList[ENEMY_02_LEFT_LEG]->textureID = LoadTGA("Image//Enemy_02_UV.tga");

	meshList[ENEMY_02_LEFT_KNEE] = MeshBuilder::GenerateOBJ("Enemy 2 left knee", "OBJ//Enemy02_left_knee.obj");
	meshList[ENEMY_02_LEFT_KNEE]->textureID = LoadTGA("Image//Enemy_02_UV.tga");

	meshList[ENEMY_02_RIGHT_ARM] = MeshBuilder::GenerateOBJ("Enemy 2 Right arm", "OBJ//Enemy02_right_arm.obj");
	meshList[ENEMY_02_RIGHT_ARM]->textureID = LoadTGA("Image//Enemy_02_UV.tga");

	meshList[ENEMY_02_RIGHT_LEG] = MeshBuilder::GenerateOBJ("Enemy 2 Right leg", "OBJ//Enemy02_right_leg.obj");
	meshList[ENEMY_02_RIGHT_LEG]->textureID = LoadTGA("Image//Enemy_02_UV.tga");

	meshList[ENEMY_02_RIGHT_KNEE] = MeshBuilder::GenerateOBJ("Enemy 2 Right knee", "OBJ//Enemy02_right_knee.obj");
	meshList[ENEMY_02_RIGHT_KNEE]->textureID = LoadTGA("Image//Enemy_02_UV.tga");


	//====================== Player Assets ==============================================//

	meshList[PLAYER_BODY] = MeshBuilder::GenerateOBJ("player body", "OBJ//Player_Body.obj");
	meshList[PLAYER_BODY]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[RIGHT_SHOULDER] = MeshBuilder::GenerateOBJ("player right shoulder", "OBJ//Right_shoulder.obj");
	meshList[RIGHT_SHOULDER]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[RIGHT_ARM] = MeshBuilder::GenerateOBJ("player right arm", "OBJ//Player_Right_Arm.obj");
	meshList[RIGHT_ARM]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[RIGHT_HAND] = MeshBuilder::GenerateOBJ("player right hand", "OBJ//Right_Hand.obj");
	meshList[RIGHT_HAND]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[LEFT_SHOULDER] = MeshBuilder::GenerateOBJ("player left shoulder", "OBJ//Left_shoulder.obj");
	meshList[LEFT_SHOULDER]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[LEFT_ARM] = MeshBuilder::GenerateOBJ("player left arm", "OBJ//Player_Left_Arm.obj");
	meshList[LEFT_ARM]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[LEFT_HAND] = MeshBuilder::GenerateOBJ("player left hand", "OBJ//Left_Hand.obj");
	meshList[LEFT_HAND]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[RIGHT_LEG] = MeshBuilder::GenerateOBJ("player right leg", "OBJ//Right_leg.obj");
	meshList[RIGHT_LEG]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[RIGHT_KNEE] = MeshBuilder::GenerateOBJ("player right knee", "OBJ//Right_knee.obj");
	meshList[RIGHT_KNEE]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[LEFT_LEG] = MeshBuilder::GenerateOBJ("player left leg", "OBJ//Left_leg.obj");
	meshList[LEFT_LEG]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[LEFT_KNEE] = MeshBuilder::GenerateOBJ("player left knee", "OBJ//Left_knee.obj");
	meshList[LEFT_KNEE]->textureID = LoadTGA("Image//Player_UV.tga");

	meshList[PLAYER_SWORD] = MeshBuilder::GenerateOBJ("player sword", "OBJ//Player_Sword.obj");
	meshList[PLAYER_SWORD]->textureID = LoadTGA("Image//Sword_Texture.tga");

	meshList[PLAYER_GUN] = MeshBuilder::GenerateOBJ("player gun", "OBJ//Player_Gun.obj");
	meshList[PLAYER_GUN]->textureID = LoadTGA("Image//Gun_Texture.tga");

	//====================== Environment Assets =========================================//

	meshList[CRATE_MODEL] = MeshBuilder::GenerateOBJ("Crate", "OBJ//Crate.obj");
	meshList[CRATE_MODEL]->textureID = LoadTGA("Image//CrateTexture.tga");

	meshList[KEY_MODEL] = MeshBuilder::GenerateOBJ("key", "OBJ//Key.obj");
	meshList[KEY_MODEL]->textureID = LoadTGA("Image//KeyTexture.tga");

	meshList[HEALTH_MODEL] = MeshBuilder::GenerateOBJ("key", "OBJ//Health.obj");
	meshList[HEALTH_MODEL]->textureID = LoadTGA("Image//HealthTexture.tga");

	meshList[POLICECAR_MODEL] = MeshBuilder::GenerateOBJ("police car", "OBJ//PoliceCar.obj");
	meshList[POLICECAR_MODEL]->textureID = LoadTGA("Image//PoliceCarTexture.tga");

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
	projectionStack.LoadMatrix(projection);

	//Lights
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 100, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);


	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	player.setPlayerHealth(5);
	player.setPlayerShield(5);
	player.setPlayerAbility(5);
}

void Scene01::Update(double dt)
{
	float LSPEED = 10.f;
	//static float E01_RotaLimit = 1;
	player.setPosition(camera.target);
	

	if (Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}
	if (Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}

	Key_Rotation += (float)(100 * dt);
	Health_Rotation += (float)(100 * dt);

	if (Application::IsKeyPressed('0'))
	{
		enableLight = false;
	}
	if (Application::IsKeyPressed('9'))
	{
		enableLight = true;
	}

	//CollisionCheck();
	
	//Scene transition
	if (camera.target.x >= 30 && camera.target.x <= 60 && camera.target.z >= -300 && camera.target.z <= -250 /* &&  key */)
	{
		SceneManager::SetNextSceneID(2);
	}


	if (Application::IsKeyPressed(VK_F2))
	{
		SceneManager::SetNextSceneID(2);
	}
	else if (Application::IsKeyPressed(VK_F3))
	{
		SceneManager::SetNextSceneID(3);
	}

	//Player icon position update
	pi_tx = (int)camera.target.x * 19 / 600 + 140;
	pi_ty = (565 - (int)camera.target.z) * 19 / 565 + 82;

	//===================== UI related stuff ==============
	//if (Application::IsKeyPressed('O'))
	//{
	//	player.setPlayerHealth(player.getCurrentHealth() - 1); //for damage
	//}
	//else if (Application::IsKeyPressed('P'))
	//{
	//	player.setPlayerHealth(player.getCurrentHealth() + 1);// for health pack
	//}
	//if (Application::IsKeyPressed('K'))
	//{
	//	player.setPlayerShield(player.getCurrentShield() - 1); //for damage
	//}
	//else if (Application::IsKeyPressed('L'))
	//{
	//	player.setPlayerShield(player.getCurrentShield() + 1);// for regen
	//}
	//if (Application::IsKeyPressed('N'))
	//{
	//	player.setPlayerAbility(player.getCurrentAbility() - 1); //for damage
	//}
	//else if (Application::IsKeyPressed('M'))
	//{
	//	player.setPlayerAbility(player.getCurrentAbility() + 1);// for regen
	//}
	//====================================================================
	camera.Update(dt, &rotateAngle);

	
	//Enemy Update
	for (unsigned int i = 0; i < EnemyContainer.size(); i++)
	{
		EnemyContainer[i].Update(dt, EnemyContainer, player);
		if (Application::IsKeyPressed('F')
			&& (player.getPosition() - EnemyContainer[i].getPosition()).Length() <= 30)
		{
			//std::cout << EnemyContainer[i].enemyHealth << std::endl;
			EnemyContainer[i].enemyHealth - 1;
			EnemyContainer[i].enemyDead = true;
			if (EnemyContainer[i].enemyHealth <= 0)
			{
				EnemyContainer[i].enemyDead = true;
			}
		}
		else
		{
			!Application::IsKeyPressed('F');
		}
		//Bullet Update
		if (EnemyContainer[i].enemyDead == false)
		{
			for (unsigned int j = 0; j < EnemyContainer[i].BulletContainer.size(); j++)
			{
				EnemyContainer[i].BulletContainer[j].Update(dt, &player);
			}
		}
	}
	xcoord = "X-Target:" + std::to_string(camera.target.x);
	zcoord = "Z-Target:" + std::to_string(camera.target.z);
}

void Scene01::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Scene01::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void Scene01::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

}

void Scene01::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();

	//to do: scale and translate accordingly

	modelStack.Translate((float)x, (float)y, 0);
	modelStack.Scale((float)sizex, (float)sizey, 1);

	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}


void Scene01::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey, int rotatez)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 160, 0, 120, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();

	//to do: scale and translate accordingly

	modelStack.Translate((float)x, (float)y, 0);
	modelStack.Rotate((float)rotatez, 0, 0, 1);
	modelStack.Rotate(camera.rotateBody, 0, 0, 1);
	modelStack.Scale((float)sizex, (float)sizey, 1);

	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Scene01::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Mtx44 MVP;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);

	modelStack.LoadIdentity();

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x,
			light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//======================= Scene Rendering ==========================
	RenderMesh(meshList[GEO_AXES], false);

	//Environment
	RenderMap();
	RenderCrates();
	RenderHealthPack();

	//Enemy
	RenderEnemies();
	RenderEnemyBullets();

	//Player
	RenderPlayer();
	RenderPlayerUI();

	RenderMinimap();

	RenderTextOnScreen(meshList[GEO_TEXT], xcoord, Color(1, 0, 0), 3, 0, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], zcoord, Color(0, 0, 1), 3, 0, 1);
	//==================================================================

}

void Scene01::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);

	for (int i = 0; i < NUM_GEOMETRY; i++)
	{
		if (meshList[i] != NULL)
		{
			delete meshList[i];
		}
	}

	BuildingContainer.clear();
}

void Scene01::RenderMinimap()
{
	RenderMeshOnScreen(meshList[MAP], 70, 50, 19, 19);
	RenderMeshOnScreen(meshList[PLAYER_ICON], pi_tx, pi_ty, 4, 4, -90); // render mesh on screen which can rotate
	RenderMeshOnScreen(meshList[OVERLAY], 70, 38, 29, 5);
	RenderTextOnScreen(meshList[GEO_TEXT], "    City ", Color(1, 0, 0), 1.5, 41, 25);
}

Enemy Scene01::MakeEnemy(Vector3 newPos, float newSizeX, float newSizeZ, EnemyType ThisType)
{
	Enemy NewEnemy(newPos, newSizeX, newSizeZ, ThisType);

	return NewEnemy;
}

GameObject Scene01::MakeGameObject(Vector3 newPos, float newSizeX, float newSizeZ)
{
	GameObject NewGameObject(newPos, newSizeX, newSizeZ);

	return NewGameObject;
}

void Scene01::RenderEnemies()
{
	for (unsigned int i = 0; i < EnemyContainer.size(); i++)
	{
		if (EnemyContainer[i].GetEnemyType() == Ranged)
		{
			if (EnemyContainer[i].enemyDead == false)
			{
				modelStack.PushMatrix();
				modelStack.Translate(EnemyContainer[i].getPosition().x, 30, EnemyContainer[i].getPosition().z);
				modelStack.Rotate(EnemyContainer[i].ENEMY_TURN, 0, 1, 0);
				modelStack.Scale(10.f, 10.f, 10.f);
				modelStack.PushMatrix();

				modelStack.PushMatrix();
				modelStack.Translate(1.f, 2.5f, 0.f);
				modelStack.Rotate(EnemyContainer[i].ANIM_ROTATE, 1, 0, 0);
				RenderMesh(meshList[ENEMY_01_LEG], false);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				modelStack.Translate(-1.f, 2.5f, 0.f);
				modelStack.Rotate(-EnemyContainer[i].ANIM_ROTATE, 1, 0, 0);
				RenderMesh(meshList[ENEMY_01_LEG], false);
				modelStack.PopMatrix();

				RenderMesh(meshList[ENEMY_01_WAIST], false);
				modelStack.PopMatrix();

				RenderMesh(meshList[ENEMY_01_BODY], false);
				modelStack.PopMatrix();
			}
		}
		//else
		//{
		//	//Put Enemy 2 Render here(Melee)
		//	modelStack.PushMatrix();// body
		//	modelStack.Translate(EnemyContainer[i].getPosition().x, 30, EnemyContainer[i].getPosition().z);
		//	modelStack.Rotate(EnemyContainer[i].ENEMY_TURN, 0, 1, 0);
		//	modelStack.Scale(20.f, 20.f, 20.f);
		//	//======================= Left arm
		//	modelStack.PushMatrix();
		//	modelStack.Translate(0.8f, 4.7f, 0.f);

		//	modelStack.PushMatrix();
		//	modelStack.Translate(0.4f, -0.8f, 0.f);

		//	RenderMesh(meshList[ENEMY_02_LEFT_ARM], false);
		//	modelStack.PopMatrix();

		//	RenderMesh(meshList[ENEMY_02_LEFT_SHLDR], false);
		//	modelStack.PopMatrix();
		//	//======================= Left leg
		//	modelStack.PushMatrix();
		//	modelStack.Translate(0.2f, 3.f, -0.5f);
		//	modelStack.Rotate(EnemyContainer[i].ANIM_ROTATE, 1, 0, 0);
		//	modelStack.PushMatrix();

		//	modelStack.Translate(0.5f, -1.4f, -0.3f);
		//	modelStack.Rotate(-EnemyContainer[i].ANIM_ROTATE, 1, 0, 0);
		//	RenderMesh(meshList[ENEMY_02_LEFT_KNEE], false);
		//	modelStack.PopMatrix();

		//	RenderMesh(meshList[ENEMY_02_LEFT_LEG], false);
		//	modelStack.PopMatrix();
		//	//======================= Right leg

		//	modelStack.PushMatrix();
		//	modelStack.Translate(-0.2f, 3.f, -0.5f);
		//	modelStack.Rotate(-EnemyContainer[i].ANIM_ROTATE, 1, 0, 0);

		//	modelStack.PushMatrix();
		//	modelStack.Translate(-0.5f, -1.4f, -0.3f);
		//	modelStack.Rotate(EnemyContainer[i].ANIM_ROTATE, 1, 0, 0);

		//	RenderMesh(meshList[ENEMY_02_RIGHT_KNEE], false);
		//	modelStack.PopMatrix();

		//	RenderMesh(meshList[ENEMY_02_RIGHT_LEG], false);
		//	modelStack.PopMatrix();

		//	//======================= right arm

		//	modelStack.PushMatrix();
		//	modelStack.Translate(-0.8f, 4.7f, 0.f);

		//	RenderMesh(meshList[ENEMY_02_RIGHT_ARM], false);
		//	modelStack.PopMatrix();

		//	RenderMesh(meshList[ENEMY_02_BODY], false);
		//	modelStack.PopMatrix();
		//}

	}
}

void Scene01::RenderCrates()
{
	modelStack.PushMatrix();
	modelStack.Rotate(45.f, 0, -1, 0);
	modelStack.Translate(450.f, 10.f, 90.f);
	modelStack.Scale(10.f, 10.f, 10.f);
	RenderMesh(meshList[CRATE_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-400.f, 10.f, 390.f);
	modelStack.Scale(10.f, 10.f, 10.f);
	RenderMesh(meshList[CRATE_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(210.f, 10.f, -430.f);
	modelStack.Scale(10.f, 10.f, 10.f);
	RenderMesh(meshList[CRATE_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-150.f, 10.f, -430.f);
	modelStack.Scale(10.f, 10.f, 10.f);
	RenderMesh(meshList[CRATE_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(260.f, 10.f, 110.f);
	modelStack.Scale(10.f, 10.f, 10.f);
	RenderMesh(meshList[CRATE_MODEL], enableLight);
	modelStack.PopMatrix();
}

void Scene01::RenderHealthPack()
{
	modelStack.PushMatrix();
	modelStack.Translate(-400.f, 30.f, 385.f);
	modelStack.Rotate(Health_Rotation, 0, 1, 0);
	modelStack.Scale(7.f, 7.f, 7.f);
	RenderMesh(meshList[HEALTH_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-150.f, 30.f, -430.f);
	modelStack.Rotate(Health_Rotation, 0, 1, 0);
	modelStack.Scale(7.f, 7.f, 7.f);
	RenderMesh(meshList[HEALTH_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(210.f, 30.f, -430.f);
	modelStack.Rotate(Health_Rotation, 0, -1, 0);
	modelStack.Scale(7.f, 7.f, 7.f);
	RenderMesh(meshList[HEALTH_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(260.f, 30.f, 110.f);
	modelStack.Rotate(Health_Rotation, 0, -1, 0);
	modelStack.Scale(7.f, 7.f, 7.f);
	RenderMesh(meshList[HEALTH_MODEL], enableLight);
	modelStack.PopMatrix();
}

void Scene01::RenderPlayerUI()
{
	RenderMeshOnScreen(meshList[HEALTH_BAR], 17, 58, 35, 3);
	player.healthIconVecX = 10.f;
	player.shieldIconVecX = 10.f;
	player.abilityIconVecX = 10.f;
	for (int i = 0; i < player.getCurrentHealth(); i++)
	{
		RenderMeshOnScreen(meshList[HEALTH], player.healthIconVecX, 58.f, 3.5f, 3.5f);
		player.healthIconVecX += 5;
	}
	RenderMeshOnScreen(meshList[SHIELD_BAR], 17, 55, 35, 3);

	for (int i = 0; i < player.getCurrentShield(); i++)
	{
		RenderMeshOnScreen(meshList[SHIELD], player.shieldIconVecX, 55.f, 3.5f, 3.5f);
		player.shieldIconVecX += 5;
	}
	RenderMeshOnScreen(meshList[ABILITY_BAR], 17, 52, 35, 3);

	for (int i = 0; i < player.getCurrentAbility(); i++)
	{
		RenderMeshOnScreen(meshList[ABILITY], player.abilityIconVecX, 52.f, 3.5f, 3.5f);
		player.abilityIconVecX += 5;
	}
	RenderTextOnScreen(meshList[GEO_TEXT], "HP", Color(1, 0, 0), 2, 2, 29);
	RenderTextOnScreen(meshList[GEO_TEXT], "SP", Color(0, 1, 1), 2, 2, 27.5);
	RenderTextOnScreen(meshList[GEO_TEXT], "AP", Color(1, 1, 0), 2, 2, 26);
}

void Scene01::RenderMap()
{
	modelStack.PushMatrix();
	RenderMesh(meshList[FLOOR_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[BUILDINGS_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[TALL_BUILDINGS_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[WALL_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(255.f, 30.f, 385.f);
	modelStack.Rotate(Key_Rotation, 0, 1, 0);
	modelStack.Scale(2.f, 2.f, 2.f);
	RenderMesh(meshList[KEY_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350.f, 30.f, 30.f);
	modelStack.Rotate(180.f, -1, 0, 0);
	modelStack.Scale(30.f, 30.f, 30.f);
	RenderMesh(meshList[POLICECAR_MODEL], enableLight);
	modelStack.PopMatrix();
}

void Scene01::RenderPlayer()
{
	//Body
	modelStack.PushMatrix();
	modelStack.Translate(camera.target.x, camera.target.y + 40, camera.target.z);
	//modelStack.Rotate(-180.f, 0, 1, 0);
	modelStack.Rotate(camera.rotateBody, 0, 1, 0);
	modelStack.Scale(10.f, 10.f, 10.f);
	//Right arm
	modelStack.PushMatrix();
	modelStack.Translate(-0.5f, 3.2f, -0.3f);
	modelStack.Rotate(camera.rotateArms, 1, 0, 0);
	modelStack.Rotate(camera.rotateArmR, 1, 0, 0); // attack

	modelStack.PushMatrix();
	modelStack.Translate(-0.1f, -0.3f, -0.2f);
	modelStack.Rotate(camera.rotateArmR, 1, 0, 0); // attack
	//modelStack.Rotate(camera.rotateHandR, 1, 0, 0); // attack
	//modelStack.Rotate(-camera.rotateArms, 1, 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-0.4f, -0.6f, 0.f);
	modelStack.Rotate(camera.rotateHandR, -1, 0, 0); // attack
	modelStack.Rotate(70, 0, 1, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-0.1f, -0.3f, 0.f);

	RenderMesh(meshList[PLAYER_SWORD], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[RIGHT_HAND], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[RIGHT_ARM], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[RIGHT_SHOULDER], enableLight);
	modelStack.PopMatrix();
	//Left arm
	modelStack.PushMatrix();
	modelStack.Translate(0.5f, 3.1f, 0.4f);
	modelStack.Rotate(-camera.rotateArms, 1, -1, 0);
	//modelStack.Rotate(-camera.rotateArmR, 1, 0, 0); // attack

	modelStack.PushMatrix();
	modelStack.Translate(-0.2f, 0.f, 0.5f);
	modelStack.Rotate(-camera.rotateArms, 0, 1, 0);
	modelStack.Rotate(-camera.rotateArmL, 1, 0, 0); // attack
	modelStack.Rotate(-90, 0, 0, 1);

	modelStack.PushMatrix();
	modelStack.Translate(-0.7f, -0.1f, 0.1f);
	modelStack.Rotate(-20, 1, 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-0.4f, 0.f, -0.1f);

	RenderMesh(meshList[PLAYER_GUN], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[LEFT_HAND], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[LEFT_ARM], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[LEFT_SHOULDER], enableLight);
	modelStack.PopMatrix();

	//Right leg
	modelStack.PushMatrix();
	modelStack.Translate(0.1f, 2.2f, -0.3f);
	modelStack.Rotate(-camera.rotateLegs, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Translate(-0.4f, -0.8f, -0.2f);
	modelStack.Rotate(-camera.rotateLegs, 1, -1, 0);

	RenderMesh(meshList[RIGHT_KNEE], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[RIGHT_LEG], enableLight);
	modelStack.PopMatrix();

	//Left leg
	modelStack.PushMatrix();
	modelStack.Translate(0.3f, 2.2f, 0.1f);
	modelStack.Rotate(camera.rotateLegs, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.2f, -0.6f, 0.4f);
	modelStack.Rotate(camera.rotateLegs, 1, 0, 0);

	RenderMesh(meshList[LEFT_KNEE], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[LEFT_LEG], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[PLAYER_BODY], enableLight);
	modelStack.PopMatrix();
}

void Scene01::RenderEnemyBullets()
{
	for (unsigned int i = 0; i < EnemyContainer.size(); i++)
	{
		if (EnemyContainer[i].enemyDead == false)
		{
			//Bullet Update
			for (unsigned int j = 0; j < EnemyContainer[i].BulletContainer.size(); j++)
			{
				modelStack.PushMatrix();
				modelStack.Translate(EnemyContainer[i].BulletContainer[j].getPosition().x,
					EnemyContainer[i].BulletContainer[j].getPosition().y,
					EnemyContainer[i].BulletContainer[j].getPosition().z);
				//modelStack.Rotate(EnemyContainer[i].ENEMY_TURN, 0, 1, 0);

				modelStack.PushMatrix();
				modelStack.Translate(3.f, 25.f, 0.f);
				modelStack.Scale(3.f, 3.f, 3.f);
				RenderMesh(meshList[ENEMY_01_BULLET], enableLight);
				modelStack.PopMatrix();
				modelStack.PopMatrix();




				//modelStack.PushMatrix();
				//modelStack.Translate(EnemyContainer[i].BulletContainer[j].getPosition().x,
				//	EnemyContainer[i].BulletContainer[j].getPosition().y,
				//	EnemyContainer[i].BulletContainer[j].getPosition().z);
				////modelStack.Rotate(EnemyContainer[i].ENEMY_TURN, 0, 1, 0);

				//modelStack.PushMatrix();
				//modelStack.Translate(-3.f, 25.f, 0.f);
				//modelStack.Scale(3.f, 3.f, 3.f);
				//RenderMesh(meshList[ENEMY_01_BULLET], enableLight);
				//modelStack.PopMatrix();
				//modelStack.PopMatrix();
			}
		}
	}
}
