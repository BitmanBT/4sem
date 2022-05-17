#include "game.h"

Game::Game()
{
    view->setDrawer(std::bind(&Game::drawAll, this));

    for (int i = 0; i < numRabbits; i++)
        rabbits.push_back(randomCoord());
}

Game::~Game()
{}

Snake& Game::getSnake()
{
    Snake snake;

    coord StartCoord;
    StartCoord.first = (view->getCurSize()).first / 2;
    StartCoord.second = (view->getCurSize()).second / 2;

    for (int i = 0; i < 3; i++)
    {
        snake.body.push_back(StartCoord);
        StartCoord.first--;
    }

    snake.snake_color = COLOR::YELLOW;

    snakes.push_back(snake);

    return snakes.back();
}

bool Game::drawAll()
{
    //int iter = 1;
    
    for (auto rabbit : rabbits)
    {
        view->draw(rabbit);
    }

    for (auto& snake : snakes)
    {
        view->draw(snake);
        snakeMoves(snake);
    }

    for (auto snake = snakes.begin(); snake != snakes.end(); snake++)
    {
        if (snake->snake_status == STATUS::DEAD)
            return true;

        if (snake->snake_status != STATUS::FED)
        {
            auto point = snake->body.back();
            view->clrPoint(point);
            snake->body.pop_back();
        }
        else
            snake->snake_status = STATUS::ALIVE;
    }

    //iter = (iter + 1) % TimeBetweenRabbits;
    if (/*!iter &&*/ (rabbits.size() < numRabbits))
        rabbits.push_back(randomCoord());

    return false;
}

const coord Game::randomCoord()
{
    std::uniform_int_distribution<int> distributionX(2, (view->getCurSize()).first - 3);
    std::uniform_int_distribution<int> distributionY(2, (view->getCurSize()).second - 3);

    int x = distributionX(gen_);
    int y = distributionY(gen_);

    coord random;
    random.first = x;
    random.second = y;

    return checkIfSnake(random);
}

const coord Game::checkIfSnake(coord& random)
{
    bool toChange = false;

    auto beforeChanging = random;

    while (true)
    {
        for (auto OurSnake : snakes)
        {
            for (auto point : OurSnake.body)
            {
                if ((random.first == point.first) && (random.second == point.second))
                {
                    toChange = true;
                    break;
                }
            }
        }

        if (toChange)
        {
            if (random.first != 2)
                random.first--;
            else
                random.first++;

            if (beforeChanging.first == random.first)
            {
                if (random.second != 2)
                    random.second--;
                else
                    random.second++;
            }

            toChange = false;
        }
        else
            break;
    }

    return random;
}

void Game::snakeMoves(Snake& snake)
{
    auto head = snake.body.front();

    switch (snake.snake_direction)
    {
        case DIRECTION::UPWARD:
        {
            head.second--;
            if (head.second == 1)
                snake.snake_status = STATUS::DEAD;
            break;
        }
        case DIRECTION::LEFT:
        {
            head.first--;
            if (head.first == 1)
                snake.snake_status = STATUS::DEAD;
            break;
        }
        case DIRECTION::RIGHT:
        {
            head.first++;
            auto v = View::getView(NULL);
            if (head.first == (v->getCurSize()).first)
                snake.snake_status = STATUS::DEAD;
            break;
        }
        case DIRECTION::DOWNWARD:
        {
            head.second++;
            auto v = View::getView(NULL);
            if (head.second == (v->getCurSize()).second)
                snake.snake_status = STATUS::DEAD;
            break;
        }
    }

    for (auto point : snake.body)
    {
        if ((point.first == head.first) && (point.second == head.second))
            snake.snake_status = STATUS::DEAD;
    }

    for (auto point = rabbits.begin(); point != rabbits.end(); point++)
    {
        if (*point == head)
        {
            snake.snake_status = STATUS::FED;
            auto eaten = point;
            point--;
            rabbits.erase(eaten);
        }
    }

    snake.body.push_front(head);

    /*switch (snake.snake_direction)
    {
        case DIRECTION::UPWARD:
        {
            for (auto point : snake.body)
                point.second--;
            break;
        }
        case DIRECTION::LEFT:
        {
            for (auto point : snake.body)
                point.first--;
            break;
        }
        case DIRECTION::RIGHT:
        {
            for (auto point : snake.body)
                point.first++;
            break;
        }
        case DIRECTION::DOWNWARD:
        {
            for (auto point : snake.body)
                point.second++;
            break;
        }
    }*/
}

/*void Game::checkSnakeStatus(Snake& snake)
{
}*/