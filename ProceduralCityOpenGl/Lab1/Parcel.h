#pragma once

#include "includeDependencies.h"

#include "Vertex.h"
#include "Square.h"
#include "Cube.h"
#include "FonctionUtilitaire.h"
#include "TextureLoader\Texture_Loader.h"

#include <iostream>
#include <vector>

class Parcel
{
public:
	Parcel(float pTransY, float pTransX, float pScale, float pHeight, GLuint pTexture, GLuint pGrassTexture);
	~Parcel();
	
	void draw();

private:
	void putSquareIntoBuffer(Square pSquare);
	void putCubeIntoBuffer(Cube pCube);

	void createParcel(Square pSquare, bool top);
	void createCubeFromSquare(Square pSquare, bool pTop);

	std::vector<Square> squareList;
	GLuint* vaoSquare;

	std::vector<Cube> cubeList;
	GLuint* vaoCube;

	GLuint texture;
	GLuint grass;

	float height;
};

