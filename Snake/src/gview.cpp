#include "gview.h"

using namespace sf;

GView::GView() : cur_size{60, 60}, div_size(5), window(VideoMode(cur_size.first * div_size, cur_size.second * div_size), "Snake")
{
	window.setFramerateLimit(30);
}

GView::~GView() {}

void GView::drawBox() {}

void GView::run() 
{	
	while (window.isOpen())
	{
		Event event;
		bool Looser = false;

		window.clear(Color(250, 220, 100, 0));

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (Looser == false)
			{
				char pressed;

				switch (event.key.code)
				{
				case Keyboard::W:
					pressed = 'w';
					break;
				case Keyboard::A:
					pressed = 'a';
					break;
				case Keyboard::D:
					pressed = 'd';
					break;
				case Keyboard::S:
					pressed = 's';
					break;
				default:
					break;
				}

				if (event.type == Event::KeyPressed)
					keyHandlerFunc(pressed);
			}
			else
				window.close();
		}

		Looser = drawAll();
		window.display();

		if (Looser)
			window.close();
	}
}

void GView::draw() {}

void GView::draw(coord& rabbit)
{
	CircleShape circle;
	
	circle.setRadius(div_size);
	circle.setFillColor(Color::Blue);
	circle.setPosition(Vector2f(rabbit.first * div_size, rabbit.second * div_size));
	
	window.draw(circle);
}

void GView::draw(Snake& snake)
{
	for (auto point = snake.body.begin(); point != snake.body.end(); point++)
	{
		CircleShape circle;

		circle.setRadius(div_size);
		circle.setFillColor(Color::Red);
		circle.setPosition(Vector2f(point->first * div_size, point->second * div_size));

		window.draw(circle);
	}
}

void GView::clrPoint(coord& point)
{
	RectangleShape toClear;

	toClear.setSize(Vector2f(div_size, div_size));
	toClear.setFillColor(Color::Yellow);
	toClear.setPosition(Vector2f(point.first * div_size, point.second * div_size));

	window.draw(toClear);
}

void GView::youLost() {}

void GView::setDrawer(drawer drawFunc) { drawAll = drawFunc; }

void GView::setKeyHandler(keyHandler keyHandler) { keyHandlerFunc = keyHandler; }

const coord GView::getCurSize() { return cur_size; }