#ifndef HUMAN_H
#define HUMAN_H

#include "game.h"

class Human
{
	Snake& snake;

	void onKey(char key);

public:
	Human(Snake& snake);
	~Human();
};

#endif // HUMAN_H