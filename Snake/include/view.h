#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <list>

using rabbit = std::pair<int, int>;

class View
{
    static View* obj;

public:
    
    static View* getView(const char * value);
    virtual void run() = 0;
    virtual void draw() = 0;
    virtual void DrawRabbits(const std::list<rabbit>& rabbits) = 0;
    virtual ~View() {}
};

#endif // VIEW_H