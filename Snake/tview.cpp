#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <sys/ioctl.h>
#include "tview.h"

bool QUIT = 0;

struct size
{
    size_t cols;
    size_t lines;
};

void TView::draw()
{
    clrscr();

    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    struct size cur_size;
    cur_size.cols = w.ws_col - 1;
    cur_size.lines = w.ws_row - 1;
    
    box(&cur_size);
}

void TView::run()
{
    //setvbuf(stdout, NULL, _IONBF, sizeof(char));
    while (!QUIT)
    {
        draw();
        usleep(1000);
    }
}

void TView::gotoxy(int x, int y)
{
    printf("\e[%d;%dH", y, x);
}

void TView::clrscr()
{
    printf("\e[H\e[J");
}

void TView::put(char c)
{
    printf("%c", c);
    fflush(stdout);
}

void TView::putstr(char* s)
{
    printf("%s\n", s);
    fflush(stdout);
}

void TView::setcolor(int color)
{
    printf("\e[%dm", color);
}

void TView::hline(size_t cols, size_t cur_line)
{
    gotoxy(1, cur_line);
    char* s = new char[cols];
    for (size_t i = 0; i < cols; i++)
        s[i] = '-';
    putstr(s);
}

void TView::vline(size_t lines, size_t cur_col)
{
    for (size_t i = 2; i <= lines - 1; i++)
    {
        gotoxy(cur_col, i);
        put('|');
    }
}

void TView::box(struct size* cur_size)
{
    setcolor(32);
    hline(cur_size->cols, 1);
    hline(cur_size->cols, cur_size->lines);
    vline(cur_size->lines, 1);
    vline(cur_size->lines, cur_size->cols);
    setcolor(97);
}