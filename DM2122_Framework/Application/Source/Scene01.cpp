#include "Scene01.h"
#include "Application.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include "shader.hpp"
#include "Utility.h"
#include "LoadTGA.h"


Scene01::Scene01()
{
}

Scene01::~Scene01()
{
}

void Scene01::Init()
{
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

	//meshList[FLOOR_MODEL] = MeshBuilder::GenerateOBJ("floor", "OBJ//Scene01//v1//floor.obj");
	//meshList[FLOOR_MODEL]->textureID = LoadTGA("Image//Scene01//floor.tga");

	//meshList[BUILDINGS_MODEL] = MeshBuilder::GenerateOBJ("buildings", "OBJ//Scene01//v1//buildings.obj");
	//meshList[BUILDINGS_MODEL]->textureID = LoadTGA("Image//Scene01//buildings.tga");

	//meshList[TALL_BUILDINGS_MODEL] = MeshBuilder::GenerateOBJ("tall buildings", "OBJ//Scene01//v1//tall_buildings.obj");
	//meshList[TALL_BUILDINGS_MODEL]->textureID = LoadTGA("Image//Scene01//tall_buildings.tga");

	meshList[FLOOR_MODEL] = MeshBuilder::GenerateOBJ("floor", "OBJ//Scene01//v2//floor.obj");
	meshList[FLOOR_MODEL]->textureID = LoadTGA("Image//Scene01//floor.tga");

	meshList[BUILDINGS_MODEL] = MeshBuilder::GenerateOBJ("buildings", "OBJ//Scene01//v2//buildings.obj");
	meshList[BUILDINGS_MODEL]->textureID = LoadTGA("Image//Scene01//buildings.tga");

	meshList[TALL_BUILDINGS_MODEL] = MeshBuilder::GenerateOBJ("tall buildings", "OBJ//Scene01//v2//tall_buildings.obj");
	meshList[TALL_BUILDINGS_MODEL]->textureID = LoadTGA("Image//Scene01//tall_buildings.tga");

	meshList[WALL_MODEL] = MeshBuilder::GenerateOBJ("wall", "OBJ//Scene01//v2//wall.obj");

	//meshList[WALL_MODEL]->textureID = LoadTGA("Image//Scene01//wall.tga");

	//====================== Enemy 01 Assets =============================================
	meshList[ENEMY_01_BODY] = MeshBuilder::GenerateOBJ("Enemy body", "OBJ//Enemy_01_Body.obj");
	meshList[ENEMY_01_BODY]->textureID = LoadTGA("Image//Enemy_01.tga");

	meshList[ENEMY_01_WAIST] = MeshBuilder::GenerateOBJ("tall buildings", "OBJ//Enemy_01_Waist.obj");
	meshList[ENEMY_01_WAIST]->textureID = LoadTGA("Image//Enemy_01.tga");

	meshList[ENEMY_01_LEG] = MeshBuilder::GenerateOBJ("tall buildings", "OBJ//Enemy_01_Leg.obj");
	meshList[ENEMY_01_LEG]->textureID = LoadTGA("Image//Enemy_01.tga");

	//===================================================================================

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

}
void Scene01::createEnemy(double _dt)
{


	static float E01_RotaLimit = 1;
	static float E01_RotationFaceLimit = 1;
	enemy[0] = Vector3(0, 0, 0);
	enemy[1] = Vector3(100, 0, 100);
	enemy[2] = Vector3(-100, 0, -100);
	for (int i = 0; i < 3; i++)
	{
		Vector3 distance = (camera.target - enemy[i]);
		if ((enemy[i] - camera.target).Length() <= 100)
		{
			detectPlayer = true;
		}
		else
		{
			detectPlayer = false;
			int resetE01_rota = 0 - E01_Rotation[i];
			E01_Rotation[i] += (float)(5 * _dt* resetE01_rota);
		}
		if (detectPlayer == true)
		{
			E01_RotationFace[i] = Math::RadianToDegree(atan2(distance.x, distance.z));

			if ((enemy[i] - camera.target).Length() >= 0)
			{

				if ((enemy[i].x - camera.target.x) <= 0)
				{
					enemy[i].x += (float)(10 * _dt);
				}
				else if (enemy[i].x - camera.target.x >= 0)
				{
					enemy[i].x -= (float)(10 * _dt);
				}
				if ((enemy[i].z - camera.target.z) <= 0)
				{
					enemy[i].z += (float)(10 * _dt);
				}
				else if (E01.z - camera.target.z >= 0)
				{
					enemy[i].z -= (float)(10 * _dt);
				}
			}
			E01_Rotation[i] += (float)(100 * _dt * E01_RotaLimit);
			if (E01_Rotation[i] < -40 || E01_Rotation[i] > 40)
			{
				E01_RotaLimit *= -1;
			}
		}
	}

}
void Scene01::Update(double dt)
{
	float LSPEED = 10.f;
	static float E01_RotaLimit = 1;
	

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
	//===================Enemy 01 animation =======================
	/*if (Application::IsKeyPressed(VK_UP))
	{
		E01_Rotation += (float)(100 * dt * E01_RotaLimit);
		if (E01_Rotation < -40 || E01_Rotation > 40)
		{
			E01_RotaLimit *= -1;
		}
	}
	if (E01_Rotation != 0 && !Application::IsKeyPressed(VK_UP))
	{
		int resetE01_rota = 0 - E01_Rotation;
		E01_Rotation += (float)(5 * dt* resetE01_rota);
	}*/
	//============================================================
	Key_Rotation += (float)(100 * dt);
	Health_Rotation += (float)(100 * dt);

	//===================Enemy 01  ===============================
	createEnemy(dt);
	/*Vector3 distance = (camera.target - E01);
	static float E01_RotaLimit = 1;
	static float E01_RotationFaceLimit = 1;

	if ((E01 - camera.target).Length() <= 100)
	{
	detectPlayer = true;
	}
	else
	{
	detectPlayer = false;
	int resetE01_rota = 0 - E01_Rotation;
	E01_Rotation += (float)(5 * dt* resetE01_rota);
	}
	if (detectPlayer == true)
	{
	E01_RotationFace = Math::RadianToDegree(atan2(distance.x, distance.z));

	if ((E01 - camera.target).Length() >= 0)
	{

	if ((E01.x - camera.target.x) <= 0)
	{
	E01.x += (float)(10 * dt);
	}
	else if (E01.x - camera.target.x >= 0)
	{
	E01.x -= (float)(10 * dt);
	}
	if ((E01.z - camera.target.z) <= 0)
	{
	E01.z += (float)(10 * dt);
	}
	else if (E01.z - camera.target.z >= 0)
	{
	E01.z -= (float)(10 * dt);
	}
	}
	E01_Rotation += (float)(100 * dt * E01_RotaLimit);
	if (E01_Rotation < -40 || E01_Rotation > 40)
	{
	E01_RotaLimit *= -1;
	}
	}*/
	//============================================================

	/*
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	*/

	if (Application::IsKeyPressed('0'))
	{
		enableLight = false;
	}
	if (Application::IsKeyPressed('9'))
	{
		enableLight = true;
	}

	if (Application::IsKeyPressed('5'))
	{
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}


	camera.Update(dt, &rotateAngle);

	/*if ((camera.position - Vector3(100, 0, 0)).Length() < 20)
	{
		camera.position.Set(0, 0, 50);
		Application::setScene(2);
	}*/
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
void Scene01::RenderMeshOnScreen(Mesh* mesh, int x, int y, int
	sizex, int sizey)
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

	modelStack.Translate(10, 10, 0);
	modelStack.Scale(5, 5, 1);

	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
void Scene01::RenderEnemy01()
{
	modelStack.PushMatrix();
	modelStack.Translate(enemy[0].x, 30, enemy[0].z);
	modelStack.Rotate(E01_RotationFace[0], 0, 1, 0);
	modelStack.Scale(10, 10, 10);

	modelStack.PushMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1, 2.5, 0);
	modelStack.Rotate(E01_Rotation[0], 1, 0, 0);
	RenderMesh(meshList[ENEMY_01_LEG], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1, 2.5, 0);
	modelStack.Rotate(-E01_Rotation[0], 1, 0, 0);
	RenderMesh(meshList[ENEMY_01_LEG], false);
	modelStack.PopMatrix();

	RenderMesh(meshList[ENEMY_01_WAIST], false);
	modelStack.PopMatrix();

	RenderMesh(meshList[ENEMY_01_BODY], false);
	modelStack.PopMatrix();

	//==================================

	modelStack.PushMatrix();
	modelStack.Translate(enemy[1].x, 30, enemy[1].z);
	modelStack.Rotate(E01_RotationFace[1], 0, 1, 0);
	modelStack.Scale(10, 10, 10);

	modelStack.PushMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1, 2.5, 0);
	modelStack.Rotate(E01_Rotation[1], 1, 0, 0);
	RenderMesh(meshList[ENEMY_01_LEG], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1, 2.5, 0);
	modelStack.Rotate(-E01_Rotation[1], 1, 0, 0);
	RenderMesh(meshList[ENEMY_01_LEG], false);
	modelStack.PopMatrix();

	RenderMesh(meshList[ENEMY_01_WAIST], false);
	modelStack.PopMatrix();

	RenderMesh(meshList[ENEMY_01_BODY], false);
	modelStack.PopMatrix();

	//==================================
	modelStack.PushMatrix();
	modelStack.Translate(enemy[2].x, 30, enemy[2].z);
	modelStack.Rotate(E01_RotationFace[2], 0, 1, 0);
	modelStack.Scale(10, 10, 10);

	modelStack.PushMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1, 2.5, 0);
	modelStack.Rotate(E01_Rotation[2], 1, 0, 0);
	RenderMesh(meshList[ENEMY_01_LEG], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1, 2.5, 0);
	modelStack.Rotate(-E01_Rotation[2], 1, 0, 0);
	RenderMesh(meshList[ENEMY_01_LEG], false);
	modelStack.PopMatrix();

	RenderMesh(meshList[ENEMY_01_WAIST], false);
	modelStack.PopMatrix();

	RenderMesh(meshList[ENEMY_01_BODY], false);
	modelStack.PopMatrix();
}

void Scene01::RenderCrates()
{
	modelStack.PushMatrix();
	modelStack.Rotate(45, 0, -1, 0);
	modelStack.Translate(450, 10, 90);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[CRATE_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-400, 10, 390);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[CRATE_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(210, 10, -430);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[CRATE_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-150, 10, -430);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[CRATE_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(260, 10, 110);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[CRATE_MODEL], enableLight);
	modelStack.PopMatrix();
}

void Scene01::RenderHealthPack()
{
	modelStack.PushMatrix();
	modelStack.Translate(-400, 30, 385);
	modelStack.Rotate(Health_Rotation, 0, 1, 0);
	modelStack.Scale(7, 7, 7);
	RenderMesh(meshList[HEALTH_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-150, 30, -430);
	modelStack.Rotate(Health_Rotation, 0, 1, 0);
	modelStack.Scale(7, 7, 7);
	RenderMesh(meshList[HEALTH_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(210, 30, -430);
	modelStack.Rotate(Health_Rotation, 0, -1, 0);
	modelStack.Scale(7, 7, 7);
	RenderMesh(meshList[HEALTH_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(260, 30, 110);
	modelStack.Rotate(Health_Rotation, 0, -1, 0);
	modelStack.Scale(7, 7, 7);
	RenderMesh(meshList[HEALTH_MODEL], enableLight);
	modelStack.PopMatrix();
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

	//scene ============================================================
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(camera.target.x, camera.target.y + 40, camera.target.z);
	modelStack.Scale(5, 5, 5);
	RenderMesh(meshList[GEO_SPHERE], enableLight);
	modelStack.PopMatrix();

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
	modelStack.Translate(255, 30, 385);
	modelStack.Rotate(Key_Rotation, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[KEY_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(350, 30, 30);
	modelStack.Rotate(180, -1, 0, 0);
	modelStack.Scale(30, 30, 30);
	RenderMesh(meshList[POLICECAR_MODEL], enableLight);
	modelStack.PopMatrix();

	RenderEnemy01();
	RenderCrates();
	RenderHealthPack();

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
}
