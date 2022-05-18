#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <utility>
#include <functional>
#include <time.h>

#include <SFML/Graphics.hpp>

using drawer = std::function<bool()>;
using keyHandler = std::function<void(int)>;

const int M = 20;
const int N = 10;

sf::Clock lock_;
float Time = 0;
float timer = 0, delay = 0.3;

int colorNum = 1;

bool beginGame = true;

int field[M][N] = { 0 };

int figures[7][4] =
{
	1, 3, 5, 7, // I
	2, 4, 5, 7, // S
	3, 5, 4, 6, // Z
	3, 5, 4, 7, // T
	2, 3, 5, 7, // L
	3, 5, 7, 6, // J
	2, 3, 4, 5, // O
};

struct Point
{
	int x, y;
} a[4], b[4];

class View
{
	sf::RenderWindow window;

	View* obj;

public:
	View();
	~View();

	static View* getView();

	void setDrawer(drawer drawFunc);
	void setKeyHandler(keyHandler keyHandler);

	void run();
};

#endif // VIEW_H