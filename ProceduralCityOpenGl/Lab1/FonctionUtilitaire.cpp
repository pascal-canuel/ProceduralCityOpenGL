#include "FonctionUtilitaire.h"



FonctionUtilitaire::FonctionUtilitaire()
{
}


FonctionUtilitaire::~FonctionUtilitaire()
{
}

GLclampf FonctionUtilitaire::RandomColorValue()
{
	double random = rand() % 100 + 1;
	return (GLclampf)(random / 100);
}

// 0-90-180
float FonctionUtilitaire::RandAngle() {
	int random = rand() % 3;
	return random * 90;
}

float FonctionUtilitaire::RandTex()
{
	return rand() % 3;
}

float FonctionUtilitaire::RandTexHouse()
{
	return rand() % 2;
}

bool FonctionUtilitaire::RandBool()
{
	return rand() % 2;
}

float FonctionUtilitaire::RandHeight()
{
	double random = rand() % 10 + 1;
	return random / 100;
}
