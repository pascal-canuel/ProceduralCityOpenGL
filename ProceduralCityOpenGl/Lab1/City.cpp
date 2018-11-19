#include "City.h"



City::City()
{
	vecBigTex.push_back(texLoad.CreateTexture2D((char*)"Texture/building.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB));
	vecBigTex.push_back(texLoad.CreateTexture2D((char*)"Texture/nightBuilding.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB));
	vecBigTex.push_back(texLoad.CreateTexture2D((char*)"Texture/window.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB));

	vecHouseTex.push_back(texLoad.CreateTexture2D((char*)"Texture/house1.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB));
	vecHouseTex.push_back(texLoad.CreateTexture2D((char*)"Texture/house2.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB));

	grassTexture = texLoad.CreateTexture2D((char*)"Texture/grass.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB);

	roadTexture = texLoad.CreateTexture2D((char*)"Texture/black.bmp", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB);
}


City::~City()
{

}

void City::generate()
{
	glGenVertexArrays(1, &vaoGround);
	glBindVertexArray(vaoGround);
	createGround();
	glBindVertexArray(0);

	Gaussian gaussian;
	gaussian.getGaussianKernel(20, 20, 4, 4);

	float scale = (float)1 / gridSize;

	for (int y = 0; y < gridSize; y++) {
		for (int x = 0; x < gridSize; x++) {
			float transY = (float)y * 2 / gridSize - 1 + scale;
			float transX = (float)x * 2 / gridSize - 1 + scale;

			if(gaussian.kernel[y][x] > 0.40f)
				gridParcel[y][x] = new Parcel(transY, transX, scale, gaussian.kernel[y][x], vecBigTex[FonctionUtilitaire::RandTex()], grassTexture);
			else
				gridParcel[y][x] = new Parcel(transY, transX, scale, gaussian.kernel[y][x], vecHouseTex[FonctionUtilitaire::RandTexHouse()], grassTexture);
		}
	}
}

void City::deleteVao()
{
	glDeleteVertexArrays(1, &vaoGround);
}

void City::drawVao()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, roadTexture);

	glBindVertexArray(vaoGround);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	for (int y = 0; y < gridSize; y++) {
		for (int x = 0; x < gridSize; x++) {
			gridParcel[y][x]->draw();
		}
	}
}

void City::createGround()
{
	//replace with vertex 
	Vertex ground[4];

	glm::vec3 color(0, 0, 0);

	ground[0] = Vertex(glm::vec2(-1, -1), color);
	ground[1] = Vertex(glm::vec2(1, -1), color);
	ground[2] = Vertex(glm::vec2(-1, 1), color);
	ground[3] = Vertex(glm::vec2(1, 1), color);

	ground[0].position.z += 0.0001;
	ground[1].position.z += 0.0001;
	ground[2].position.z += 0.0001;
	ground[3].position.z += 0.0001;

	ground[0].texture = glm::vec2(0, 0);
	ground[1].texture = glm::vec2(0, 1);
	ground[2].texture = glm::vec2(1, 1);
	ground[3].texture = glm::vec2(1, 0);

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

