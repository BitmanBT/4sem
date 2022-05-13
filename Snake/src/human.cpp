#include "human.h"

Human::Human(Snake& snake) : snake(snake)
{	
	auto view = View::getView(NULL);
	view->setKeyHandler(std::bind(&Human::onKey, this, std::placeholders::_1));
}

Human::~Human() {}

void Human::onKey(char key)
{
	switch (tolower(key))
	{
		case 'w': 
			snake.snake_direction = DIRECTION::UPWARD;
			break;
		case 'a':
			snake.snake_direction = DIRECTION::LEFT;
			break;
		case 'd':
			snake.snake_direction = DIRECTION::RIGHT;
			break;
		case 's':
			snake.snake_direction = DIRECTION::DOWNWARD;
			break;
		default:
			break;
	}
}