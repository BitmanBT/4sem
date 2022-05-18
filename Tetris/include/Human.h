#ifndef HUMAN_H
#define HUMAN_H

#include "Game.h"

class Human
{
	Game& game;
	
	void onKey(sf::Keyboard::Key key);

public:
	Human(Game& game);
	~Human();
};

#endif // HUMAN_H