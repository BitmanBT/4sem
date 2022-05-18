#include "View.h"

View* View::obj = NULL;

View::View() : window(sf::VideoMode(320, 480), "Tetris") {}

View::~View()
{
	window.close();
}

View* View::getView()
{
	if (obj)
		return obj;

	obj = new View();

	return obj;
}

void View::run()
{
	srand(time(0));

	sf::Texture texture;
	texture.loadFromFile("../sprites/tiles.png");

	sf::Sprite sprite(texture);
	sprite.setTextureRect(IntRect(0, 0, 18, 18));
	
	while (window.isOpen())
	{
		Time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += Time;
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
				KeyHandlerFunc(event.key.code);
		}

		drawAll();

		window.clear(Color::White);

		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0)
					continue;
				sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				sprite.setPosition(j * 18, i * 18);
				sprite.move(28, 31);
				window.draw(sprite);
			}

		for (int i = 0; i < 4; i++)
		{
			sprite.setTexturesRect(IntRect(colorNum * 18, 0, 18, 18));
			sprite.setPosition(a[i].x * 18, a[i].y * 18);
			sprite.move(28, 31);
			window.draw(sprite);
		}

		window.display();
	}
}

void View::setDrawer(drawer drawFunc) { drawAll = drawFunc; }
void View::setKeyHandler(keyHandler keyHandler) { keyHandlerFunc = keyHandler; }