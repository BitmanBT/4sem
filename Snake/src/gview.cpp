#include "gview.h"

using namespace sf;

GView::GView() : cur_size{50, 50}, div_size(25), window(VideoMode(cur_size.first * div_size, cur_size.second * div_size), "Snake")
{
	window.setFramerateLimit(60);
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

void GView::draw(coord& rabbit) {}

void GView::draw(Snake& snake) {}

void GView::clrPoint(coord& point) {}

void GView::youLost() {}

void GView::setDrawer(drawer drawFunc) { drawAll = drawFunc; }

void GView::setKeyHandler(keyHandler keyHandler) { keyHandlerFunc = keyHandler; }

const coord GView::getCurSize() {}