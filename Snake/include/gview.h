#ifndef GVIEW_H
#define GVIEW_H

#include <SFML/Graphics.hpp>

#include "view.h"

class GView : public View
{
    coord cur_size;
    int div_size;
    
    sf::RenderWindow window;

    drawer drawAll;
    keyHandler keyHandlerFunc;

public:
	GView();
	~GView();

    virtual void drawBox();
    virtual void run();
    virtual void draw();
    virtual void draw(coord& rabbit);
    virtual void draw(Snake& snake);
    virtual void clrPoint(coord& point);
    virtual void youLost();

    virtual void setDrawer(drawer);
    virtual void setKeyHandler(keyHandler);

    virtual const coord getCurSize();
};

#endif //_GVIEW_H_