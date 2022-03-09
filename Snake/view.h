#ifndef VIEW_H
#define VIEW_H

class View
{
    int x, y, z;
    static View* obj;

public:
    static View* getView(const char * value);
    virtual void run() = 0;
    virtual void draw() = 0;
};

#endif // VIEW_H