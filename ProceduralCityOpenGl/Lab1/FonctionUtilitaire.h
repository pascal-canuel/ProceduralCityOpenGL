#pragma once

#include "includeDependencies.h"

class FonctionUtilitaire
{
public:
	FonctionUtilitaire();
	~FonctionUtilitaire();
	static GLclampf RandomColorValue();
	static float RandAngle();
	static float RandTex();
	static float RandTexHouse();
	static bool RandBool();
	static float RandHeight();
};

