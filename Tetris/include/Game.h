#ifndef GAME_H
#define GAME_H

#include <functional>

#include "View.h"

using namespace sf;

class Game
{
	View* view = View::getView();

	void update();
	bool check();

public:
	int dx = 0;
	bool rotate = false;

	Game();
	~Game();

	bool drawAll();
};

#endif // GAME_H