#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <csignal>

#include "tview.h"

struct termios old_term;

bool QUIT = false;

struct size
{
    size_t cols;
    size_t lines;
};

void SignHandler(int n)
{
    QUIT = true;
}

TView::TView()
{
    struct termios term;
    tcgetattr(0, &term);
    
    old_term = term;

    cfmakeraw(&term);
    term.c_lflag |= ISIG;
    tcsetattr(0, TCSANOW, &term);
    signal(SIGINT, SignHandler);
}

TView::~TView() 
{
    tcsetattr(0, TCSANOW, &old_term);
}

void TView::run()
{
    while (!QUIT)
    {
        draw();

        usleep(500000);
    }
}

void TView::draw()
{
    clrscr();
    
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    struct size cur_size;
    cur_size.cols = w.ws_col - 1;
    cur_size.lines = w.ws_row - 1;
    
    clrscr();

    setcolor(32, 43);

    box(&cur_size);
}

void TView::gotoxy(int x, int y)
{
    printf("\e[%d;%dH", y, x);
}

void TView::clrscr()
{
    printf("\e[H\e[J");
}

void TView::putc(char c)
{
    printf("%c", c);
    fflush(stdout);
}

void TView::puts(char* s)
{
    printf("%s\n", s);
    fflush(stdout);
}

void TView::setcolor(int color)
{
    printf("\e[%dm", color);
}

void TView::setcolor(int f_color, int b_color) 
{
    printf("\e[%d;%dm", f_color, b_color);
}

void TView::hline(size_t cols, size_t cur_line)
{
    gotoxy(1, cur_line);
    char* s = new char[cols];
    for (size_t i = 0; i < cols; i++)
        s[i] = '*';
    puts(s);
}

void TView::vline(size_t lines, size_t cur_col)
{
    for (size_t i = 2; i <= lines - 1; i++)
    {
        gotoxy(cur_col, i);
        putc('*');
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