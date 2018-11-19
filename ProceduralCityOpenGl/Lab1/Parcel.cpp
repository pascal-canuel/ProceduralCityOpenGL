#include "Parcel.h"



Parcel::Parcel(float pTransY, float pTransX, float pScale, float pHeight, GLuint pTexture, GLuint pGrassTexture)
{
	height = pHeight; 
	texture = pTexture;
	grass = pGrassTexture;

	Square mainSquare1 = Square(glm::vec2(-1, 0), glm::vec2(1, 0), glm::vec2(-1, 1), glm::vec2(1, 1), glm::vec3(1, 0, 0));
	Square mainSquare2 = Square(glm::vec2(-1, 0), glm::vec2(1, 0), glm::vec2(-1, -1), glm::vec2(1, -1), glm::vec3(0, 1, 0));

	createParcel(mainSquare1, true);
	createParcel(mainSquare2, false);

	glm::mat4x4 rot = glm::mat4(1.0);
	glm::mat4x4 ech = glm::mat4(1.0);
	glm::mat4x4 trans = glm::mat4(1.0);

	//matrices de rotation
	rot = glm::rotate(rot, glm::radians(FonctionUtilitaire::RandAngle()), glm::vec3(0.0, 0.0, 1.0));
	
	//matrice d'échelle
	ech = glm::scale(ech, glm::vec3(pScale, pScale, pScale));

	//matrice de translation
	trans = glm::translate(trans, glm::vec3(pTransX, pTransY, 0));

	vaoSquare = new GLuint[squareList.size()];
	glGenVertexArrays(squareList.size(), vaoSquare);

	vaoCube = new GLuint[cubeList.size()];
	glGenVertexArrays(cubeList.size(), vaoCube);

	for (int i = 0; i < squareList.size(); i++) {
		squareList[i].bl.position = glm::vec3(trans * rot * ech * glm::vec4(squareList[i].bl.position, 1));
		squareList[i].tl.position = glm::vec3(trans * rot * ech * glm::vec4(squareList[i].tl.position, 1));
		squareList[i].br.position = glm::vec3(trans * rot * ech * glm::vec4(squareList[i].br.position, 1));
		squareList[i].tr.position = glm::vec3(trans * rot * ech * glm::vec4(squareList[i].tr.position, 1));

		cubeList[i].bot.bl.position = glm::vec3(trans * rot * ech * glm::vec4(cubeList[i].bot.bl.position, 1));
		cubeList[i].bot.tl.position = glm::vec3(trans * rot * ech * glm::vec4(cubeList[i].bot.tl.position, 1));
		cubeList[i].bot.br.position = glm::vec3(trans * rot * ech * glm::vec4(cubeList[i].bot.br.position, 1));
		cubeList[i].bot.tr.position = glm::vec3(trans * rot * ech * glm::vec4(cubeList[i].bot.tr.position, 1));

		cubeList[i].top.bl.position = glm::vec3(trans * rot * ech * glm::vec4(cubeList[i].top.bl.position, 1));
		cubeList[i].top.tl.position = glm::vec3(trans * rot * ech * glm::vec4(cubeList[i].top.tl.position, 1));
		cubeList[i].top.br.position = glm::vec3(trans * rot * ech * glm::vec4(cubeList[i].top.br.position, 1));
		cubeList[i].top.tr.position = glm::vec3(trans * rot * ech * glm::vec4(cubeList[i].top.tr.position, 1));

		glBindVertexArray(vaoSquare[i]);
		putSquareIntoBuffer(squareList[i]);
		glBindVertexArray(0);

		glBindVertexArray(vaoCube[i]);
		putCubeIntoBuffer(cubeList[i]);
		glBindVertexArray(0);
	}
}


Parcel::~Parcel()
{

}

void Parcel::draw()
{
	for (int i = 0; i < squareList.size(); i++) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, grass);

		glBindVertexArray(vaoSquare[i]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(vaoCube[i]);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Parcel::putSquareIntoBuffer(Square pSquare)
{
	Vertex ground[4];

	ground[0] = pSquare.bl;
	ground[1] = pSquare.br;
	ground[2] = pSquare.tl;
	ground[3] = pSquare.tr;

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground), ground, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground), ground, GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));

	GLuint texturebuffer;
	glGenBuffers(1, &texturebuffer);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground), ground, GL_STREAM_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texture)));
}

void Parcel::putCubeIntoBuffer(Cube pCube)
{
	
	Vertex cube[8];

	pCube.bot.bl.texture = glm::vec2(1, 0);
	cube[0] = pCube.bot.bl;
	pCube.bot.br.texture = glm::vec2(0, 0);
	cube[1] = pCube.bot.br;

	pCube.bot.tl.texture = glm::vec2(0, 0);
	cube[2] = pCube.bot.tl;
	pCube.bot.tr.texture = glm::vec2(1, 0);
	cube[3] = pCube.bot.tr;

	pCube.top.bl.texture = glm::vec2(1, 1);
	cube[4] = pCube.top.bl;
	pCube.top.br.texture = glm::vec2(0, 1);
	cube[5] = pCube.top.br;
	pCube.top.tl.texture = glm::vec2(0, 1);
	cube[6] = pCube.top.tl;
	pCube.top.tr.texture = glm::vec2(1, 1);
	cube[7] = pCube.top.tr;

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));

	// TODO remove color and apply a random texture

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));

	unsigned int Indices[] = {
		0, 1, 2,
		1, 2, 3,
		4, 5, 6,
		5, 6, 7,
		1, 3, 7,
		1, 5, 7,
		0, 2, 6,
		0, 4, 6,
		6, 2, 3,
		6, 3, 7,
		0, 1, 4,
		1, 4, 5
	};

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	GLuint texturebuffer;
	glGenBuffers(1, &texturebuffer);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, texturebuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STREAM_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texture)));
}

void Parcel::createParcel(Square pSquare, bool top)
{
	float resize = 0.1;

	bool ret;
	ret = FonctionUtilitaire::RandBool();
	if (ret) {
		// cut vertical
		Square childSquare1 = pSquare;
		childSquare1.br.position.x = 0;
		childSquare1.tr.position.x = 0;
		childSquare1.ChangeColor(glm::vec3(0, 1, 0));

		childSquare1.Resize(resize, top);

		squareList.push_back(childSquare1);
		createCubeFromSquare(childSquare1, top);

		Square childSquare2 = pSquare;
		childSquare2.bl.position.x = 0;
		childSquare2.tl.position.x = 0;
		childSquare2.ChangeColor(glm::vec3(0, 1, 0));

		childSquare2.Resize(resize, top);

		squareList.push_back(childSquare2);
		createCubeFromSquare(childSquare2, top);
	}
	else {
		// cut horizontal
		ret = FonctionUtilitaire::RandBool();
		if (ret) {

			float axisY;
			if (top)
				axisY = 0.5;
			else
				axisY = -0.5;

			Square childSquare1 = pSquare;
			childSquare1.bl.position.y = axisY;
			childSquare1.br.position.y = axisY;
			childSquare1.ChangeColor(glm::vec3(0, 1, 0));

			childSquare1.Resize(resize, top);

			squareList.push_back(childSquare1);
			createCubeFromSquare(childSquare1, top);

			Square childSquare2 = pSquare;
			childSquare2.tl.position.y = axisY;
			childSquare2.tr.position.y = axisY;
			childSquare2.ChangeColor(glm::vec3(0, 1, 0));

			childSquare2.Resize(resize, top);

			squareList.push_back(childSquare2);
			createCubeFromSquare(childSquare2, top);
		}
		else {
			pSquare.ChangeColor(glm::vec3(0, 1, 0));
			pSquare.Resize(resize, top);
	
			squareList.push_back(pSquare);
			createCubeFromSquare(pSquare, top);
		}
	}
}

void Parcel::createCubeFromSquare(Square pSquare, bool pTop)
{
	pSquare.Resize(0.1, pTop);
	pSquare.ChangeColor();

	pSquare.bl.position.z -= 0.0001;
	pSquare.br.position.z -= 0.0001;
	pSquare.tl.position.z -= 0.0001;
	pSquare.tr.position.z -= 0.0001;

	Square top = pSquare;

	float baseHeight = height * 2;
	float randomHeight = FonctionUtilitaire::RandHeight();

	top.bl.position.z -= baseHeight + randomHeight;
	top.br.position.z -= baseHeight + randomHeight;
	top.tl.position.z -= baseHeight + randomHeight;
	top.tr.position.z -= baseHeight + randomHeight;

	top.ChangeColor();

	Cube cube = Cube(pSquare, top);

	cubeList.push_back(cube);
}


