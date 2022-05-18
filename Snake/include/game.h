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
	std::list<Snake> snakes;

	const coord randomCoord();
	const coord checkIfSnake(coord& random);

	View* view = View::getView();
	std::random_device gen_;

	void snakeMoves(Snake& snake);

public:
	Game();
	~Game();

	bool drawAll();

	Snake& getSnake();

	std::list<coord>& getRabbits() { return rabbits; }
	std::list<Snake>& getSnakes() { return snakes; }
};

#endif // GAME_H