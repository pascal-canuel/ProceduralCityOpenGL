#pragma once

#include "Square.h"

struct Cube {
	Cube() {};
	Cube(Square pBot, Square pTop) {
		bot = pBot;
		top = pTop;
	}

	Square bot, top;
};