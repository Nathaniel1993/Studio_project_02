#include "Scene02.h"
#include "Application.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include "shader.hpp"
#include "Utility.h"
#include "LoadTGA.h"
#include "SceneManager.h"

Scene02::Scene02()
{
}

Scene02::~Scene02()
{
}

void Scene02::Init()
{
	// Init VBO here
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Set background colour to dark blue

	glEnable(GL_CULL_FACE);

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

	camera.Init(Vector3(30, 40, 980),
		Vector3(10, 0, 960),
		Vector3(0, 1, 0));

	camera.rotateBody = 180;
	
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//Scene02//dialogue.tga");

	//======================= Minimap ======================================================
	meshList[PLAYER_ICON] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[PLAYER_ICON]->textureID = LoadTGA("Image//Minimap//arrowhead.tga");

	meshList[OVERLAY] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[OVERLAY]->textureID = LoadTGA("Image//Minimap//overlay.tga");

	meshList[MAP] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[MAP]->textureID = LoadTGA("Image//Minimap//minimap2.tga");

	meshList[MAP_DOORS] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[MAP_DOORS]->textureID = LoadTGA("Image//Minimap//minimap2_doors.tga");

	meshList[MAP_GATE] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[MAP_GATE]->textureID = LoadTGA("Image//Minimap//minimap2_gate.tga");
	//=====================================================================================

	meshList[FLOOR_MODEL] = MeshBuilder::GenerateOBJ("floor", "OBJ//Scene02//floor.obj");
	meshList[FLOOR_MODEL]->textureID = LoadTGA("Image//Scene02//floor.tga");

	meshList[WALL_MODEL] = MeshBuilder::GenerateOBJ("wall", "OBJ//Scene02//wall.obj");
	meshList[WALL_MODEL]->textureID = LoadTGA("Image//Scene02//wall.tga");

	meshList[BOOKS_MODEL] = MeshBuilder::GenerateOBJ("books", "OBJ//Scene02//books.obj");
	meshList[BOOKS_MODEL]->textureID = LoadTGA("Image//Scene02//books.tga");

	meshList[NPC_MODEL] = MeshBuilder::GenerateOBJ("npc", "OBJ//Scene02//NPC_Robot.obj");
	meshList[NPC_MODEL]->textureID = LoadTGA("Image//Scene02//NPC_Color.tga");

	meshList[STAIRS_MODEL] = MeshBuilder::GenerateOBJ("stairs", "OBJ//Scene02//stairs.obj");
	meshList[STAIRS_MODEL]->textureID = LoadTGA("Image//Scene02//stairs.tga");

	meshList[SWITCHES_MODEL] = MeshBuilder::GenerateOBJ("switches", "OBJ//Scene02//switch.obj");
	meshList[SWITCHES_MODEL]->textureID = LoadTGA("Image//Scene02//switches.tga");

	meshList[DESKS_MODEL] = MeshBuilder::GenerateOBJ("desks", "OBJ//Scene02//desk.obj");
	meshList[DESKS_MODEL]->textureID = LoadTGA("Image//Scene02//desks.tga");

	meshList[SOFA_MODEL] = MeshBuilder::GenerateOBJ("sofa", "OBJ//Scene02//sofa.obj");
	meshList[SOFA_MODEL]->textureID = LoadTGA("Image//Scene02//sofa.tga");

	meshList[BUTTON_MODEL] = MeshBuilder::GenerateOBJ("button", "OBJ//Scene02//button.obj");
	meshList[BUTTON_MODEL]->textureID = LoadTGA("Image//Scene02//button.tga");

	meshList[SUB_DOOR_MODEL] = MeshBuilder::GenerateOBJ("sub door", "OBJ//Scene02//subdoor.obj");

	meshList[MAIN_DOOR_MODEL] = MeshBuilder::GenerateOBJ("main door", "OBJ//Scene02//finaldoor.obj");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//System.tga");

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
	//============================================================================================//

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 2000.f);
	projectionStack.LoadMatrix(projection);

	//Lights
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 0;
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

void Scene02::Update(double dt)
{
	static float pressKey = 1;
	static float subdoor_TranslateLimit = 1.0f;
	float LSPEED = 10.f;

	if (Application::IsKeyPressed(VK_SPACE))
	{
		pressKey *= -1;
	}
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


	X_target = "X-Target:" + std::to_string(camera.target.x);
	Z_target = "Z-Target:" + std::to_string(camera.target.z);
	buttonQuest = std::to_string(buttonPressed + buttonPressed2) + "/2 Button Pressed";
	switchQuest = std::to_string(switchPressed) + "/1 Switch Pressed";
	lightswitchQuest = std::to_string(switchPressed2) + "/1 Power Swtich Pressed";

	//======== For button ====================//
	if (pressButton == true)
	{
		if (buttonPressed >= 0 && buttonPressed < 1)
		{
			buttonPressed++;
		}
	}
	if (pressButton2 == true)
	{
		if (buttonPressed2 >= 0 && buttonPressed2 < 1)
		{
			buttonPressed2++;
		}
	}
	if (buttonPressed + buttonPressed2 == 2)
	{
		mainDoorOpen = true;
	}
	if (mainDoorOpen == true)
	{
		if (maindoor_Translate < 4)
		{
			maindoor_Translate += (float)(1.0f * dt);
		}
	}
	//=========================================//

	//================ For Switch ================//
	if (pressSwitch == true)
	{
		if (switchPressed >= 0 && switchPressed < 1)
		{
			switchPressed++;
		}
	}
	if (switchPressed == 1)
	{
		subDoorOpen = true;
	}
	if (subDoorOpen == true)
	{
		if (subdoor_Translate < 4)
		{
			subdoor_Translate += (float)(1.0f * dt);
		}
	}
	//=============== For Light Switch =============//
	if (pressSwitch2 == true)
	{
		if (switchPressed2 >= 0 && switchPressed2 < 1)
		{
			switchPressed2++;
		}
	}
	if (switchPressed2 == 1)
	{
		lightsOn = true;
	}
	if (lightsOn == true)
	{
		light[0].power = 1;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	}
	//=======================================//

	if (Application::IsKeyPressed(VK_F1))
	{
		SceneManager::SetNextSceneID(1);
	}
	if (Application::IsKeyPressed(VK_F3))
	{
		SceneManager::SetNextSceneID(3);
	}

	pi_tx = camera.target.x * 19 / 980 + 140;
	pi_ty = (980 - camera.target.z) * 19 / 980 + 82;

	/*if ((camera.position - Vector3(100, 0, 0)).Length() < 20)
	{
	camera.position.Set(0, 0, 50);
	Application::setScene(2);
	}*/
}

void Scene02::RenderMesh(Mesh *mesh, bool enableLight)
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
void Scene02::RenderText(Mesh* mesh, std::string text, Color color)
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
void Scene02::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
		characterSpacing.SetToTranslation(i * 1.f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
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
void Scene02::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
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

	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 1);

	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Scene02::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey, int rotatez)
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

	modelStack.Translate(x, y, 0);
	modelStack.Rotate(rotatez, 0, 0, 1);
	modelStack.Rotate(camera.rotateBody, 0, 0, 1);
	modelStack.Scale(sizex, sizey, 1);

	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Scene02::RenderMap()
{
	modelStack.PushMatrix();
	modelStack.Scale(40, 40, 40);

	modelStack.PushMatrix();
	RenderMesh(meshList[FLOOR_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[WALL_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[BOOKS_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[STAIRS_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[SWITCHES_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[DESKS_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[SOFA_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[BUTTON_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[NPC_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, subdoor_Translate);
	RenderMesh(meshList[SUB_DOOR_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(13, 0, 0);
	modelStack.Translate(0, 0, subdoor_Translate);
	RenderMesh(meshList[SUB_DOOR_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(maindoor_Translate, 0, 0);
	RenderMesh(meshList[MAIN_DOOR_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void Scene02::Interactible()
{
	if (questOpen2)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], buttonQuest, Color(1, 0, 0), 1.5, 0, 25);
	}
	if (questOpen1)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], switchQuest, Color(1, 0, 0), 1.5, 0, 23);
	}
	if (questOpen)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], lightswitchQuest, Color(1, 0, 0), 1.5, 0, 21);
	}

	//  button in left room
	if (camera.target.x >= -440.0f && camera.target.x <= -400.0f && camera.target.z >= -110.0f && camera.target.z <= 20.0f && questOpen2) // checking if the character is at the right position
	{
		rightPos1 = true;
	}
	else if (camera.target.x <= -440.0f && camera.target.x >= -400.0f && camera.target.z <= -110.0f && camera.target.z >= 20.0f && !questOpen2) // checking if the character is at the right position
	{
		rightPos1 = false;
	}
	if (rightPos1 == true) // if character is at the right position and pressed 'Z' key, something will happen
	{
		if (Application::IsKeyPressed('Z'))
		{
			pressButton = true;
		}
	}
	else if (rightPos1 == false) // if character is not at the right position and pressed 'Z' key, something will not happen
	{
		if (Application::IsKeyPressed('Z'))
		{
			pressButton = false;
		}
	}

	// button in right room
	if (camera.target.x >= 330.0f && camera.target.x <= 350.0f && camera.target.z >= -110.0f && camera.target.z <= 30.0f && questOpen2) // checking if the character is at the right position
	{
		rightPos2 = true;
	}
	else if (camera.target.x <= 330.0f && camera.target.x >= 350.0f && camera.target.z <= -110.0f && camera.target.z >= 30.0f && !questOpen2) // checking if the character is at the right position
	{
		rightPos2 = false;
	}
	if (rightPos2 == true) // if character is at the right position and pressed 'Z' key, something will happen
	{
		if (Application::IsKeyPressed('Z'))
		{
			pressButton2 = true;
		}
	}
	else if (rightPos2 == false) // if character is not at the right position and pressed 'Z' key, something will not happen
	{
		if (Application::IsKeyPressed('Z'))
		{
			pressButton2 = false;
		}
	}

	// door switch 
	if (camera.target.x >= -800.0f && camera.target.x <= -730.0f && camera.target.z >= 400.0f && camera.target.z <= 420.0f && questOpen1) // checking if the character is at the right position
	{
		rightPos3 = true;
	}
	else if (camera.target.x <= -800.0f && camera.target.x >= -730.0f && camera.target.z <= 400.0f && camera.target.z >= 420.0f && !questOpen1) // checking if the character is at the right position
	{
		rightPos3 = false;
	}
	if (rightPos3 == true) // if character is at the right position and pressed 'Z' key, something will happen
	{
		if (Application::IsKeyPressed('Z'))
		{
			pressSwitch = true;
		}
	}
	else if (rightPos3 == false) // if character is not at the right position and pressed 'Z' key, something will not happen
	{
		if (Application::IsKeyPressed('Z'))
		{
			pressSwitch = false;
		}
	}

	// light switch
	if (camera.target.x >= 320.0f && camera.target.x <= 340.0f && camera.target.z >= 520.0f && camera.target.z <= 600.0f && questOpen) // checking if the character is at the right position
	{
		rightPos = true;
	}
	else if (camera.target.x <= 320.0f && camera.target.x >= 340.0f && camera.target.z <= 520.0f && camera.target.z >= 600.0f && !questOpen) // checking if the character is at the right position
	{
		rightPos = false;
	}
	if (rightPos == true) // if character is at the right position and pressed 'Z' key, something will happen
	{
		if (Application::IsKeyPressed('Z'))
		{
			pressSwitch2 = true;
		}
	}
	else if (rightPos == false) // if character is not at the right position and pressed 'Z' key, something will not happen
	{
		if (Application::IsKeyPressed('Z'))
		{
			pressSwitch2 = false;
		}
	}
	//NPC==================================================================================================================
	if (camera.target.x >= 520.0f && camera.target.x <= 630.0f && camera.target.z >= 800.0f && camera.target.z <= 820.0f)
	{
		RenderMeshOnScreen(meshList[GEO_QUAD], 43, 8, 90, 15);
		RenderTextOnScreen(meshList[GEO_TEXT], "Find your way out.", Color(1, 0, 0), 2, 12, 4);
	}
	//light
	if (camera.target.x >= -580.0f && camera.target.x <= -480.0f && camera.target.z >= 800.0f && camera.target.z <= 820.0f)
	{
		RenderMeshOnScreen(meshList[GEO_QUAD], 43, 8, 90, 15);
		RenderTextOnScreen(meshList[GEO_TEXT], "Find the correct switch", Color(1, 0, 0), 2, 10, 5);
		RenderTextOnScreen(meshList[GEO_TEXT], "to turn on the power.", Color(1, 0, 0), 2, 10, 4);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Z' to trigger switch.", Color(1, 0, 0), 2, 7, 3);
		questOpen = true;
	}
	//door
	if (camera.target.x >= -720.0f && camera.target.x <= -620.0f && camera.target.z >= 800.0f && camera.target.z <= 820.0f && pressSwitch2)
	{
		RenderMeshOnScreen(meshList[GEO_QUAD], 43, 8, 90, 15);
		RenderTextOnScreen(meshList[GEO_TEXT], "Find the correct switch ", Color(1, 0, 0), 2, 10, 5);
		RenderTextOnScreen(meshList[GEO_TEXT], "to open the doors.", Color(1, 0, 0), 2, 12, 4);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Z' to trigger switch.", Color(1, 0, 0), 2, 7, 3);
		questOpen1 = true;
	}
	//button
	if (camera.target.x >= -660.0f && camera.target.x <= -560.0f && camera.target.z >= 260.0f && camera.target.z <= 280.0f)
	{
		RenderMeshOnScreen(meshList[GEO_QUAD], 43, 8, 90, 15);
		RenderTextOnScreen(meshList[GEO_TEXT], "Find the correct buttons", Color(1, 0, 0), 2, 10, 5);
		RenderTextOnScreen(meshList[GEO_TEXT], "to open the gate.", Color(1, 0, 0), 2, 12, 4);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'Z' to trigger button.", Color(1, 0, 0), 2, 7, 3);
		questOpen2 = true;
	}
}

void Scene02::RenderPlayer()
{
	//Body
	modelStack.PushMatrix();
	modelStack.Translate(camera.target.x, camera.target.y + 40, camera.target.z);
	modelStack.Rotate(camera.rotateBody, 0, 1, 0);
	modelStack.Scale(20.f, 20.f, 20.f);
	//Right arm
	modelStack.PushMatrix();
	modelStack.Translate(-0.5f, 3.2f, -0.3f);
	modelStack.Rotate(camera.rotateArms, 1, 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-0.1f, -0.3f, -0.2f);
	//modelStack.Rotate(-camera.rotateArms, 1, 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-0.4f, -0.6f, 0.f);
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
	modelStack.Translate(0.5, 3.1, 0.4);
	modelStack.Rotate(-camera.rotateArms, 1, -1, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-0.2, 0, 0.5);
	modelStack.Rotate(-camera.rotateArms, 0, 1, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-0.7, -0.1, 0.1);

	modelStack.PushMatrix();
	modelStack.Translate(-0.4, 0, -0.1);

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
	modelStack.Translate(0.1, 2.2, -0.3);
	modelStack.Rotate(-camera.rotateLegs, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Translate(-0.4, -0.8, -0.2);
	modelStack.Rotate(-camera.rotateLegs, 1, -1, 0);

	RenderMesh(meshList[RIGHT_KNEE], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[RIGHT_LEG], enableLight);
	modelStack.PopMatrix();

	//Left leg
	modelStack.PushMatrix();
	modelStack.Translate(0.3, 2.2, 0.1);
	modelStack.Rotate(camera.rotateLegs, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.2, -0.6, 0.4);
	modelStack.Rotate(camera.rotateLegs, 1, 0, 0);

	RenderMesh(meshList[LEFT_KNEE], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[LEFT_LEG], enableLight);
	modelStack.PopMatrix();

	RenderMesh(meshList[PLAYER_BODY], enableLight);
	modelStack.PopMatrix();
}

void Scene02::Render()
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

	RenderPlayer();
	RenderMap();
	Interactible();

	//==================================================================
	RenderTextOnScreen(meshList[GEO_TEXT], X_target, Color(1, 0, 0), 3, 0, 19);
	RenderTextOnScreen(meshList[GEO_TEXT], Z_target, Color(0, 0, 1), 3, 0, 18);
	
	
	RenderMeshOnScreen(meshList[MAP], 70, 50, 19, 19);
	RenderMeshOnScreen(meshList[MAP_DOORS], 70, 50, 19, 19);
	RenderMeshOnScreen(meshList[MAP_GATE], 70, 50, 19, 19);
	RenderMeshOnScreen(meshList[PLAYER_ICON], pi_tx, pi_ty, 4, 4, -90); // render mesh on screen which can rotate
	RenderMeshOnScreen(meshList[OVERLAY], 70, 38, 29, 5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Building", Color(1, 0, 0), 1.5, 41, 25);

}


void Scene02::Exit()
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
