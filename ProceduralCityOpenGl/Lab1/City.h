#pragma once

#include "includeDependencies.h"
#include "Vertex.h"
#include "Parcel.h"
#include "gaussian.h"

#include "TextureLoader\Texture_Loader.h"

using namespace texCore;

class City
{
public:
	City();
	~City();

	void generate();
	void drawVao();
	void deleteVao();

private:
	void createGround();

	GLuint vaoGround;

	int gridSize = 20;
	Parcel* gridParcel[20][20];

	std::vector<GLuint> vecBigTex;
	std::vector<GLuint> vecHouseTex;

	GLuint grassTexture;
	GLuint roadTexture;

	Texture_Loader texLoad;
};

