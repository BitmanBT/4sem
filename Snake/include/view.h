#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <list>
#include <utility>
#include <functional>

using coord = std::pair<int, int>;
using drawer = std::function<bool ()>;
using keyHandler = std::function<void (int )>;

enum class DIRECTION : int { UPWARD, LEFT, RIGHT, DOWNWARD };
enum class COLOR : int { BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
enum class STATUS : int { ALIVE, DEAD, FED };

struct Snake
{
    std::list<coord> body;
    DIRECTION snake_direction = DIRECTION::RIGHT;
    COLOR snake_color = COLOR::RED;
    STATUS snake_status = STATUS::ALIVE;
};

class View
{
    static View* obj;

public:
    static View* getView(const char* value = nullptr);
    virtual void drawBox() = 0;
    virtual void run() = 0;
    virtual void draw() = 0;
    virtual void draw(coord& rabbit) = 0;
    virtual void draw(Snake& snake) = 0;
    virtual void clrPoint(coord& point) = 0;
    virtual void youLost() = 0;

    virtual void setDrawer(drawer) = 0;
    virtual void setKeyHandler(keyHandler) = 0;

    virtual const coord getCurSize() = 0;

    virtual ~View() {}
};

#endif // VIEW_H