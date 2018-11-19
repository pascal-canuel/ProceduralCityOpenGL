#pragma once

#include "includeDependencies.h"

struct Vertex
{
	Vertex() {}
	Vertex(glm::vec2 pPosition, glm::vec3 pColor) {
		position = glm::vec3(pPosition, 0);
		color = pColor;
	}

	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texture;
};