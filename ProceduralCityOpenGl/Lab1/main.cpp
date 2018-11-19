#include <iostream>

/******APIs*****/
#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies\glm\glm\gtc\matrix_transform.hpp"
#include "Dependencies\soil\src\SOIL.h"

/*****Classes personnalisées*******/
#include "ShaderLoader\Shader_Loader.h"
#include "HouseMaker\House_Maker.h"
#include "TextureLoader\Texture_Loader.h"

#include "City.h"

/**********namespaces**************/
using namespace Core;
using namespace House;
using namespace texCore;


/****Handlers globaux*****/
GLuint textureProgram;
GLuint skyboxProgram;
GLuint vaoSkybox;
GLuint gProjection;
GLuint gVue;
GLuint gModele;
GLuint texSkybox;

/******variables globales*******/


glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 7.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float multipleCouleur[4] = { 1.0,1.0,1.0,1.0 };
bool firstMouse = true;
bool firstKey = false;
GLfloat yaw = -90.0f;	
GLfloat pitch = 0.0f;
GLfloat lastX = 0;
GLfloat lastY = 0;
bool boutons[4] = { false,false,false,false };
bool warpsouris=false;
float fov = 70.0f;
City* city;

void getUniforms(GLuint *program)
{
	glUseProgram(*program);
	gProjection = glGetUniformLocation(*program, "gProjection");
	assert(gProjection != 0xFFFFFFFF);

	gVue = glGetUniformLocation(*program, "gVue");
	assert(gVue != 0xFFFFFFFF);
}

void Limites()
{
	if (cameraPos.z <= -300.0)
	{
		cameraPos.z = -300.0;
	}
	if (cameraPos.z >= 300.0)
	{
		cameraPos.z = 300.0;
	}
	if (cameraPos.x <= -300.0)
	{
		cameraPos.x = -300.0;
	}
	if (cameraPos.x >= 300.0)
	{
		cameraPos.x = 300.0;
	}
}

void deplacement()
{
	GLfloat cameraSpeed = 0.8f;
	glm::vec3 camDevant;
	camDevant.x = cameraFront.x;
	camDevant.z = cameraFront.z;

	if (boutons[0] == true) {
		cameraPos -= glm::normalize(glm::cross(camDevant, cameraUp)) * cameraSpeed;
	}
	if (boutons[1] == true) {
		cameraPos += cameraSpeed * camDevant;
	}
	if (boutons[2] == true) {
		cameraPos -= cameraSpeed * camDevant;
	}
	if (boutons[3] == true) {
		cameraPos += glm::normalize(glm::cross(camDevant, cameraUp)) * cameraSpeed;
	}

	Limites();
	
}

void drawSkybox()
{
	// skybox cube
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(skyboxProgram, "Skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texSkybox);
	glBindVertexArray(vaoSkybox);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
}

//Fonction de rappel du rendu graphique
void renduScene()
{
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 modele;

	deplacement();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	
	projection = glm::perspective(glm::radians(fov), glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT)*1.0f, 0.1f, 800.0f);
	
	getUniforms(&skyboxProgram);
	view = glm::mat4(glm::mat3(glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)));
	glUniformMatrix4fv(gProjection, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(gVue, 1, GL_FALSE, &view[0][0]);
	drawSkybox();
	
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	gModele = glGetUniformLocation(textureProgram, "gModele");
	assert(gModele != 0xFFFFFFFF);

	getUniforms(&textureProgram);
	glUniformMatrix4fv(gProjection, 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(gVue, 1, GL_FALSE, &view[0][0]);
	glUniform4fv(glGetUniformLocation(textureProgram, "color"), 1, multipleCouleur);

	glActiveTexture(GL_TEXTURE0);

	//matrices de rotation
	modele = glm::mat4(1.0);
	modele = glm::rotate(modele, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));

	//matrice de translation
	modele = glm::translate(modele, glm::vec3(0, 0, 0));

	//matrice d'échelle
	float scale = 300.0;
	modele = glm::scale(modele, glm::vec3(scale, scale, scale));

	glUniformMatrix4fv(gModele, 1, GL_FALSE, &modele[0][0]);

	//
	city->drawVao();
	//

	glutSwapBuffers();
}

void clavier(unsigned char bouton, int x, int y)
{
	switch (bouton)
	{
	case 'a':
		boutons[0] = true;
		
		break;
	case 'w':
		boutons[1] = true;
		
		break;
	case 's':
		boutons[2] = true;
		
		break;
	case 'd':
		boutons[3] = true;
		
		break;
	case 'g':
		delete city;
		city = new City();
		city->generate();
		glutPostRedisplay();

		break;
	case 'o':
		if(cameraPos.y > 0.5f)
			cameraPos.y -= 2.0f;
		break;
	case 'p':
		cameraPos.y += 2.0f;
		break;
		
	case 27:
		glutLeaveMainLoop();
		break;

	}
	
}

void releaseClavier(unsigned char bouton, int x, int y)
{

	switch (bouton)
	{
	case 'a':
		boutons[0] = false;
		break;
	case 'w':
		boutons[1] = false;
		break;
	case 's':
		boutons[2] = false;
		break;
	case 'd':
		boutons[3] = false;
		break;
		}
}

void souris(int x, int y)
{

	if (warpsouris)
	{
		warpsouris = false;
		lastX = x;
		lastY = y;
	}
	else
	{
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}

		GLfloat xoffset = x - lastX;
		GLfloat yoffset = lastY - y;
		lastX = x;
		lastY = y;

		GLfloat sensitivity = 0.3;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);

		
		warpsouris = true;
		
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		
	}

	

}
void roulette(int roue, int dir, int x, int y)
{
	if (dir == 1)
	{
		fov -= 1.0f;	
	}
	else
	{
		fov += 1.0f;
	}

	glutPostRedisplay();

}

void dessineMaison()
{	
	House_Maker maMaison;

	glBindVertexArray(vaoSkybox);
	maMaison.creeBase(1.0, 1.0, 1.0, glm::vec3(1.0, 0.0, 0.0));
	glBindVertexArray(0);

}

/*****************************************/
//Fonction d'initialisation des textures
void initTextures()
{
	Texture_Loader textureLoader;
	
	std::vector<char*> faces;
	faces.push_back("ame_nebula/purplenebula_ft.tga");
	faces.push_back("ame_nebula/purplenebula_bk.tga");
	faces.push_back("ame_nebula/purplenebula_up.tga");
	faces.push_back("ame_nebula/purplenebula_dn.tga");
	faces.push_back("ame_nebula/purplenebula_rt.tga");
	faces.push_back("ame_nebula/purplenebula_lf.tga");
	texSkybox = textureLoader.CreateSkyboxTexture(faces);
}

/*****************************************/
//Fonction d'initialisation des shaders
void initShaders()
{
	Core::Shader_Loader shaderLoader;
	textureProgram = shaderLoader.CreateProgram("vertexShader.glsl", "fragmentShader.glsl");
	skyboxProgram = shaderLoader.CreateProgram("vertSkybox.glsl", "fragSkybox.glsl");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//glUseProgram(textureProgram);

	/*gProjection = glGetUniformLocation(textureProgram, "gProjection");
	assert(gProjection != 0xFFFFFFFF);

	gVue = glGetUniformLocation(textureProgram, "gVue");
	assert(gVue != 0xFFFFFFFF);

	gModele = glGetUniformLocation(textureProgram, "gModele");
	assert(gModele != 0xFFFFFFFF);*/

	glGenVertexArrays(1, &vaoSkybox);

}
void passeTemps(int temps)
{
	multipleCouleur[temps] -= 0.5;
	temps++;

	if(temps == 4)
	{
		multipleCouleur[0] = 1.0;
		multipleCouleur[1] = 1.0;
		multipleCouleur[2] = 1.0;
		multipleCouleur[3] = 1.0;
		temps = 0;
	}
	
	glutTimerFunc(5000, passeTemps, temps);
}

/******************************************/

void fermeture()
{
	glutLeaveMainLoop();
}

//Fonction principale d'initialisation et d'exécution
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutCreateWindow("Maison 3D");
	glutFullScreen();

	/*******************/
	glewInit();

	initShaders();
		
	/******************/

	glutDisplayFunc(renduScene);
	glutCloseFunc(fermeture);
	glutKeyboardFunc(clavier);
	glutPassiveMotionFunc(souris);
	glutKeyboardUpFunc(releaseClavier);
	glutIdleFunc(renduScene);
	glutMouseWheelFunc(roulette);
	//glutTimerFunc(5000,passeTemps,0);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glClearColor(0.0f, 0.4f, 0.5f, 0.0f);

	glutSetCursor(GLUT_CURSOR_NONE);

	/***Initiaglisation de la maison****/
	initTextures();
	dessineMaison();

	city = new City();
	city->generate();

	/**********************************/
	
	glutMainLoop();

	/***************/
	glDeleteProgram(skyboxProgram);
	glDeleteProgram(textureProgram);
	/**************/

	return 0;
}

