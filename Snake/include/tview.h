#ifndef TVIEW_H
#define TVIEW_H

#include <chrono>

#include "view.h"

class TView : public View
{
    coord cur_size;

    drawer drawAll;
    keyHandler keyHandlerFunc;
    
    void gotoxy(int x, int y);
    void gotoxy(const coord& point);

    void putc(char c);
    void puts(const char* s);
    void clrscr();
    
    void setcolor(int color);
    void setcolor(int f_color, int b_color);
    void setcolor(COLOR color);

    void hline(size_t cols, size_t cur_line);
    void vline(size_t lines, size_t cur_col);

    //void check_size();

    //void UserInformation();

public:
    TView();
    ~TView();

    virtual void drawBox();
    virtual void run();
    virtual void draw();
    virtual void draw(coord& rabbit);
    virtual void draw(Snake& snake);

    virtual void setDrawer(drawer drawerFunc);
    virtual void setKeyHandler(keyHandler keyHandlerFunc);

    virtual const coord getCurSize();
};

void SignHandler(int n);

#endif // TVIEW_H