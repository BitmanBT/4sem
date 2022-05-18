#include "Game.h"

Game::Game()
{
	view->setDrawer(std::bind(&Game::drawAll, this));
}

Game::~Game() {}

void Game::drawAll()
{
	int n = rand() % 7;
	
	update();

	if (timer > delay)
	{
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].y++;
		}
		if (!check())
		{
			for (int i = 0; i < 4; i++)
				field[b[i].y][b[i].x] = colorNum;
			colorNum = 1 + rand() % 7;
			n = rand() % 7;
			for (int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}
		}
		timer = 0;
	}

	int k = M - 1;
	for (int i = M - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			if (field[i][j])
				count++;
			field[k][j] = field[i][j];
		}
		if (count < N)
			k--;
	}

	if (beginGame)
	{
		beginGame = false;
		n = rand() % 7;
		for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}
	}
	dx = 0; rotate = false; delay = 0.3;
}

void Game::update()
{
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
		a[i].x += dx;
	}

	if (!check())
		for (int i = 0; i < 4; i++)
			a[i] = b[i];

	if (rotate)
	{
		Point p = a[1];
		for (int i = 0; i < 4; i++)
		{
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}

		if (!check())
			for (int i = 0; i < 4; i++)
				a[i] = b[i];
	}
}

bool Game::check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return false;
		else if (field[a[i].y][a[i].x]) return false;

	return true;
}