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

    return snake;
}

bool Game::drawAll()
{
    int iter = 1;
    
    for (auto rabbit : rabbits)
    {
        view->draw(rabbit);
    }

    for (auto snake : snakes)
    {
        view->draw(snake);
    }

    iter = (iter++) % TimeBetweenRabbits;
    if (!iter && (rabbits.size() < numRabbits))
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