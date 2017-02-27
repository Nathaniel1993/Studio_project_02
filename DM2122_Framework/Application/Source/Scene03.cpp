#include "Scene03.h"
#include "Application.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "MeshBuilder.h"
#include "Mesh.h"
#include "shader.hpp"
#include "Utility.h"
#include "LoadTGA.h"
#include "SceneManager.h"

Scene03::Scene03()
{
}

Scene03::~Scene03()
{
}

void Scene03::Init()
{

	//Pipe_1_Container.push_back(MakeGameObject(Vector3(72.5f, 0, -275), 287.5f, 55.f));
	//Pipe_2_Container.push_back(MakeGameObject(Vector3(-272.5f, 0, -317.5f), 57.5f, 42.5f));
	//HelicopterContainer.push_back(MakeGameObject(Vector3(62.5f, 0, -135), 117.5f, 25.f));
	//RobotContainer.push_back(MakeGameObject(Vector3(70, 0, -60), 30.f, 20.f));
	//
	//Left_DoorContainer.push_back(MakeGameObject(Vector3(-45, 0, 200), 20.f, 40.f));
	//
	//Left_Horizontal_1_WallContainer.push_back(MakeGameObject(Vector3(-195, 0, 45), 165.f, 15.f)); //closer to helicopter
	//Left_Horizontal_2_WallContainer.push_back(MakeGameObject(Vector3(-187.5f, 0, 345), 172.5f, 15.f)); //closer to spawn point

	//Left_Vertical_1_WallContainer.push_back(MakeGameObject(Vector3(-45, 0, 95), 15.f, 65.f)); //closer to helicopter
	//Left_Vertical_2_WallContainer.push_back(MakeGameObject(Vector3(-45, 0, 265), 15.f, 65.f)); //closer to spawn point

	//Right_DoorContainer.push_back(MakeGameObject(Vector3(57.5f, 0, 200), 17.5f, 40.f));

	//Right_Horizontal_1_WallContainer.push_back(MakeGameObject(Vector3(200, 0, 55), 160.f, 20.f)); //closer to helicopter
	//Right_Horizontal_2_WallContainer.push_back(MakeGameObject(Vector3(187.5f, 0, 345), 172.5f, 15.f)); //closer to spawn point
	//
	//Right_Vertical_1_WallContainer.push_back(MakeGameObject(Vector3(55, 0, 95), 20.f, 62.5f)); //closer to helicopter
	//Right_Vertical_2_WallContainer.push_back(MakeGameObject(Vector3(55, 0, 275), 20.f, 55.f)); //closer to spawn point

	//scene boundaries x:330 & -330 z: 330 & -330

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

	camera.Init(Vector3(20, 40, 384),
		Vector3(0, 0, 360),
		Vector3(0, 1, 0));
	camera.rotateBody = 180;

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1.0f, 0.0f, 0.0f), 36, 36, 1.0f);

	meshList[FLOOR_MODEL] = MeshBuilder::GenerateOBJ("floor", "OBJ//Scene03//floor.obj");
	meshList[FLOOR_MODEL]->textureID = LoadTGA("Image//Scene03//floor.tga");

	meshList[HELIPAD_MODEL] = MeshBuilder::GenerateOBJ("helipad", "OBJ//Scene03//helipad.obj");
	meshList[HELIPAD_MODEL]->textureID = LoadTGA("Image//Scene03//helipad.tga");

	meshList[HELICOPTER_MODEL] = MeshBuilder::GenerateOBJ("helicopter", "OBJ//Scene03//helicopter.obj");
	meshList[HELICOPTER_MODEL]->textureID = LoadTGA("Image//Scene03//helicopter.tga");

	meshList[HELIBLADE_MODEL] = MeshBuilder::GenerateOBJ("heliblade", "OBJ//Scene03//heliblade.obj");
	meshList[HELIBLADE_MODEL]->textureID = LoadTGA("Image//Scene03//helicopter.tga");

	meshList[PIPE_MODEL] = MeshBuilder::GenerateOBJ("pipe", "OBJ//Scene03//pipe.obj");
	meshList[PIPE_MODEL]->textureID = LoadTGA("Image//Scene03//pipe.tga");

	meshList[NPC_ROBOT] = MeshBuilder::GenerateOBJ("NPC robot", "OBJ//Scene03//NPC_Robot.obj");
	meshList[NPC_ROBOT]->textureID = LoadTGA("Image//Scene03//NPC_Color.tga");

	meshList[DIALOGUE] = MeshBuilder::GenerateQuad("dialogue", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[DIALOGUE]->textureID = LoadTGA("Image//Scene02//dialogue.tga");

	meshList[RIGHT_DOOR] = MeshBuilder::GenerateOBJ("right room door", "OBJ//Scene03//right room door .obj");

	meshList[LEFT_DOOR] = MeshBuilder::GenerateOBJ("left room door", "OBJ//Scene03//left room door.obj");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//System.tga");

	//======================= Minimap ======================================================
	meshList[PLAYER_ICON] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[PLAYER_ICON]->textureID = LoadTGA("Image//Minimap//arrowhead.tga");

	meshList[OVERLAY] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[OVERLAY]->textureID = LoadTGA("Image//Minimap//overlay.tga");

	meshList[MAP] = MeshBuilder::GenerateQuad("quad", Color(1.0f, 0.0f, 0.0f), 1, 1);
	meshList[MAP]->textureID = LoadTGA("Image//Minimap//minimap3.tga");
	//=====================================================================================

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
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 1.f;
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

void Scene03::Update(double dt)
{
	if (Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}
	if (Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}

	//static float translateHeliY = 1.0f;

	HeliBladeRotation += (float)(1000 * dt);

	if (TriggerDoorOpen) //open doors
	{
		if (RightDoorTranslate < 4)
		{
			RightDoorTranslate += (float)(1.0f * dt);
		}
		if (LeftDoorTranslate < 4)
		{
			LeftDoorTranslate += (float)(1.0f * dt);
		}
		if (RightDoorTranslate > 4 && LeftDoorTranslate > 4)
		{
			TriggerDoorOpen = false;
		}
		/*Left_DoorContainer.clear();
		Right_DoorContainer.clear();*/
	}
	if (!TriggerDoorOpen && CloseRight) //closes door on the right
	{
		if (RightDoorTranslate > 0)
		{
			RightDoorTranslate -= (float)(1.0f * dt);
		}
		//Right_DoorContainer.push_back(MakeGameObject(Vector3(57.5f, 0, 200), 17.5f, 40.f)); //error! pushes character away
	}
	if (!TriggerDoorOpen && CloseLeft) //closes door on the left
	{
		if (LeftDoorTranslate > 0)
		{
			LeftDoorTranslate -= (float)(1.0f * dt);
		}
		//Left_DoorContainer.push_back(MakeGameObject(Vector3(-45, 0, 200), 20.f, 40.f)); //error! pushes character away
	}

	/*if (HeliTranslate > 1 || HeliTranslate < 0)
	{
		translateHeliY *= -1;
	}
	HeliTranslate += (float)(1.0f * translateHeliY * dt);*/

	FPS = "FPS:" + std::to_string((int)(1 / dt));
	xcoord = "X:" + std::to_string((int)(camera.target.x));
	zcoord = "Z:" + std::to_string((int)(camera.target.z));

	camera.Update(dt, &rotateAngle);

	//player icon position update
	pi_tx = (int)camera.target.x * 19 / 360 + 140;
	pi_ty = (360 - (int)camera.target.z) * 19 / 360 + 82;

	//scene changing
	if (Application::IsKeyPressed(VK_F1))
	{
		SceneManager::SetNextSceneID(1);
	}
	else if (Application::IsKeyPressed(VK_F2))
	{
		SceneManager::SetNextSceneID(2);
	}

	/*if ((camera.position - Vector3(100, 0, 0)).Length() < 20)
	{
	camera.position.Set(0, 0, 50);
	Application::setScene(2);
	}*/
}

void Scene03::RenderMesh(Mesh *mesh, bool enableLight)
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
void Scene03::RenderText(Mesh* mesh, std::string text, Color color)
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
void Scene03::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
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
void Scene03::RenderMeshOnScreen(Mesh* mesh, int x, int y, int
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

	modelStack.Translate((float)x, (float)y, 0);
	modelStack.Scale((float)sizex, (float)sizey, 1);

	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void Scene03::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey, int rotatez)
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

void Scene03::RenderPlayer()
{
	//Body
	modelStack.PushMatrix();
	modelStack.Translate(camera.target.x, camera.target.y + 40, camera.target.z);
	modelStack.Rotate(camera.rotateBody, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	//Right arm
	modelStack.PushMatrix();
	modelStack.Translate(-0.5f, 3.2f, -0.3f);
	modelStack.Rotate(camera.rotateArms, 1, 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-0.1f, -0.3f, -0.2f);
	//modelStack.Rotate(-camera.rotateArms, 1, 0, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-0.4f, -0.6f, 0);
	modelStack.PushMatrix();
	modelStack.Translate(-0.1f, -0.3f, 0);

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

	modelStack.PushMatrix();
	modelStack.Translate(-0.2f, 0, 0.5f);
	modelStack.Rotate(-camera.rotateArms, 0, 1, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-0.7f, -0.1f, 0.1f);

	modelStack.PushMatrix();
	modelStack.Translate(-0.4f, 0, -0.1f);

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

void Scene03::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Mtx44 MVP;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);

	modelStack.LoadIdentity();

	Vector3 lightDir(light[0].position.x,
		light[0].position.y, light[0].position.z);
	Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	
	//scene ============================================================
	RenderMesh(meshList[GEO_AXES], false);
	
	RenderPlayer();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, -1, 0);
	modelStack.Scale(15, 15, 15);
	
	RenderMap();
	RenderHelicopter();
	
	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_TEXT], FPS, Color(1, 0, 0), 3, 0, 19);
	RenderTextOnScreen(meshList[GEO_TEXT], xcoord, Color(1, 0, 0), 3, 0, 18);
	RenderTextOnScreen(meshList[GEO_TEXT], zcoord, Color(1, 0, 0), 3, 0, 17);

	Interactible();
	RenderMinimap();
	//==================================================================
	
}

void Scene03::Interactible()
{
	if (camera.target.x >= 39 && camera.target.x <= 74 && camera.target.z >= -56 && camera.target.z <= -24) // if character at this position, will trigger a dialogue from the NPC
	{
		Talkedto = true;
	}
	if (Talkedto) // Render the Dialogue
	{
		RenderMeshOnScreen(meshList[DIALOGUE], 43, 8, 90, 15);
		RenderTextOnScreen(meshList[GEO_TEXT], "Eliminate the enemies", Color(1, 0, 0), 2, 11, 5);
		RenderTextOnScreen(meshList[GEO_TEXT], "in both rooms in order", Color(1, 0, 0), 2, 10.5, 4);
		RenderTextOnScreen(meshList[GEO_TEXT], "to power up the helicopter.", Color(1, 0, 0), 2, 8, 3);
		Talkedto = false;
		TriggerDoorOpen = true;
	}

	if (camera.target.x >= 74 && camera.target.x <= 81 && camera.target.z >= 185 && camera.target.z <= 230) // if character at this position, right room door will close behind him upon entering
	{
		CloseRight = true;
	}
	if (camera.target.x >= -85 && camera.target.x <= -75 && camera.target.z >= 155 && camera.target.z <= 200) // if character at this position, left room door will close behind him upon entering
	{
		CloseLeft = true;
	}
	if (camera.target.x >= -25 && camera.target.x <= 1 && camera.target.z >= -110 && camera.target.z <= -90 && !EnemiesEliminated) // if character at this position and enemies in both rooms aren't eliminated, can't escape.
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Helicopter is not powered up.", Color(1, 0, 0), 2, 6, 3);
	}
}
void Scene03::RenderMap()
{
	modelStack.PushMatrix();
	RenderMesh(meshList[FLOOR_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[HELIPAD_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[PIPE_MODEL], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[NPC_ROBOT], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, RightDoorTranslate, 0);
	RenderMesh(meshList[RIGHT_DOOR], enableLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, LeftDoorTranslate, 0);
	RenderMesh(meshList[LEFT_DOOR], enableLight);
	modelStack.PopMatrix();
}
void Scene03::RenderHelicopter()
{
	modelStack.PushMatrix();
	modelStack.Scale(0.7f, 0.7f, 0.7f);
	modelStack.Translate(-13, 3, -1);
	RenderMesh(meshList[HELICOPTER_MODEL], enableLight);
		modelStack.PushMatrix();
		modelStack.Translate(0, 7, -1);
		//modelStack.Rotate(HeliBladeRotation, 0, 1, 0);
		RenderMesh(meshList[HELIBLADE_MODEL], enableLight);
		modelStack.PopMatrix();
	modelStack.PopMatrix();
}
void Scene03::RenderMinimap()
{
	RenderMeshOnScreen(meshList[MAP], 70, 50, 19, 19);
	RenderMeshOnScreen(meshList[PLAYER_ICON], pi_tx, pi_ty, 4, 4, -90); // render mesh on screen which can rotate
	RenderMeshOnScreen(meshList[OVERLAY], 70, 38, 29, 5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Rooftop", Color(1, 0, 0), 1.5, 41, 25);
}

GameObject Scene03::MakeGameObject(Vector3 newPos, float newSizeX, float newSizeZ)
{
	GameObject NewGameObject(newPos, newSizeX, newSizeZ);

	return NewGameObject;
}
void Scene03::Exit()
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

	//BuildingContainer.clear();

	/*Pipe_1_Container.clear();
	Pipe_2_Container.clear();
	HelicopterContainer.clear();
	RobotContainer.clear();
	Left_DoorContainer.clear();
	Left_Horizontal_1_WallContainer.clear();
	Left_Horizontal_2_WallContainer.clear();
	Left_Vertical_1_WallContainer.clear();
	Left_Vertical_2_WallContainer.clear();
	Right_DoorContainer.clear();
	Right_Horizontal_1_WallContainer.clear();
	Right_Horizontal_2_WallContainer.clear();
	Right_Vertical_1_WallContainer.clear();
	Right_Vertical_2_WallContainer.clear();*/
}
