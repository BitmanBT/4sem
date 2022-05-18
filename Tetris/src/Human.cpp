#include "Human.h"

Human::Human(Game& game) : game(game)
{
	auto view = View::getView();
	view->setKeyHandler(std::bind(&Human::onKey, this, std::placeholders::_1));
}

Human::~Human() {}

void Human::onKey(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Up:
		game.rotate = true;
		break;
	case sf::Keyboard::Left:
		game.dx = -1;
		break;
	case sf::Keyboard::Right:
		game.dx = 1;
		break;
	case sf::Keyboard::Down:
		auto view = View::getView();
		view->delay = 0.05;
		break;
	default:
		break;
	}
}