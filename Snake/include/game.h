#ifndef GAME_H
#define GAME_H

#include <list>
#include <utility>
#include <random>
#include <algorithm>

#include "view.h"

const int numRabbits = 3;

class Game
{
	std::list<coord> rabbits;

	const coord randomCoord();
	const coord checkIfSnake(coord& random);

	View* view = View::getView(NULL);
	std::random_device gen_;
	int TimeBetweenRabbits = 10;

public:
	Game();
	~Game();

	bool drawAll();

	std::list<coord>& getRabbits() { return rabbits; }
};

#endif // GAME_H