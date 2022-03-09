#ifndef TVIEW_H
#define TVIEW_H

#include "view.h"
#include <cstdlib>

class TView : public View
{
    void gotoxy(int x, int y);
    void clrscr();
    void put(char c);
    void putstr(char* s);
    void setcolor(int color);
    void hline(size_t cols, size_t cur_line);
    void vline(size_t lines, size_t cur_col);
    void box(struct size* cur_size);

public:
    virtual void run();
    virtual void draw();
};

#endif // TVIEW_H