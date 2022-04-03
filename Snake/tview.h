#ifndef TVIEW_H
#define TVIEW_H

#include "view.h"
#include <cstdlib>

class TView : public View
{
    void gotoxy(int x, int y);
    void clrscr();
    void putc(char c);
    void puts(char* s);
    void setcolor(int color);
    void setcolor(int f_color, int b_color);
    void hline(size_t cols, size_t cur_line);
    void vline(size_t lines, size_t cur_col);
    void box(struct size* cur_size);

public:
    TView();
    virtual void run() override;
    virtual void draw() override;
    ~TView();
};

#endif // TVIEW_H