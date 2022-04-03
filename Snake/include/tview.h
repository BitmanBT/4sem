#ifndef TVIEW_H
#define TVIEW_H

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <random>
#include <sys/poll.h>

#include "view.h"
#include "model.h"

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
    void UserInformation();
    std::pair<int, int> RandCoord(const size_t cols, const size_t lines);

public:
    
    TView();
    virtual void run() override;
    virtual void draw() override;
    virtual void DrawRabbits(const std::list<rabbit>& rabbits) override;
    ~TView();
};

void SignHandler(int n);

#endif // TVIEW_H