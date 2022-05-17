#include "human.h"

Human::Human(Snake& snake) : snake(snake)
{	
	auto view = View::getView(NULL);
	view->setKeyHandler(std::bind(&Human::onKey, this, std::placeholders::_1 ));
}

Human::~Human() {}

void Human::onKey(char key)
{
	switch (tolower(key))
	{
		case 'w':
			if (snake.snake_direction != DIRECTION::DOWNWARD)
				snake.snake_direction = DIRECTION::UPWARD;
			break;
		case 'a':
			if (snake.snake_direction != DIRECTION::RIGHT)
				snake.snake_direction = DIRECTION::LEFT;
			break;
		case 'd':
			if (snake.snake_direction != DIRECTION::LEFT)
				snake.snake_direction = DIRECTION::RIGHT;
			break;
		case 's':
			if (snake.snake_direction != DIRECTION::UPWARD)
				snake.snake_direction = DIRECTION::DOWNWARD;
			break;
		default:
			break;
	}
}