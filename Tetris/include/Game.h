#ifndef GAME_H
#define GAME_H

#include <functional>

#include "View.h"

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

	void drawAll();
};

#endif // GAME_H