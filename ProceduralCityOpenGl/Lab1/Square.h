#pragma once

#include "includeDependencies.h"
#include "FonctionUtilitaire.h"

struct Square {
	Square() {};
	Square(glm::vec2 pBL, glm::vec2 pBR, glm::vec2 pTL, glm::vec2 pTR, glm::vec3 pColor) {
		bl.position = glm::vec3(pBL, 0);
		br.position = glm::vec3(pBR, 0);
		tl.position = glm::vec3(pTL, 0);
		tr.position = glm::vec3(pTR, 0);

		bl.color = pColor;
		br.color = pColor;
		tl.color = pColor;
		tr.color = pColor;

		bl.texture = glm::vec2(0, 0);
		br.texture = glm::vec2(1, 0);
		tl.texture = glm::vec2(0, 1);
		tr.texture = glm::vec2(1, 1);
	};

	void ChangeColor() {
		glm::vec3 col = glm::vec3(FonctionUtilitaire::RandomColorValue(), FonctionUtilitaire::RandomColorValue(), FonctionUtilitaire::RandomColorValue());

		bl.color = col;
		br.color = col;
		tl.color = col;
		tr.color = col;	
	}

	void ChangeColor(glm::vec3 pColor) {

		bl.color = pColor;
		br.color = pColor;
		tl.color = pColor;
		tr.color = pColor;
	}

	void Resize(float pPad, bool pTop) {

		float axisY = 1;
		if (!pTop)
			axisY *= -1;

		bl.position.x += pPad;
		bl.position.y += pPad * axisY;

		tl.position.x += pPad;
		tl.position.y -= pPad * axisY;

		br.position.x -= pPad;
		br.position.y += pPad * axisY;

		tr.position.x -= pPad;
		tr.position.y -= pPad * axisY;
	}

	Vertex bl, br, tl, tr;
};