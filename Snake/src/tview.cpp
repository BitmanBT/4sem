#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <functional>
#include <poll.h>

#include "tview.h"
#include "game.h"

#define FG_BLACK 30
#define FG_RED 31
#define FG_GREEN 32
#define FG_YELLOW 33
#define FG_BLUE 34
#define FG_MAGENTA 35
#define FG_CYAN 36
#define FG_WHITE 37

#define BG_BLACK 40
#define BG_RED 41
#define BG_GREEN 42
#define BG_YELLOW 43
#define BG_BLUE 44
#define BG_MAGENTA 45
#define BG_CYAN 46
#define BG_WHITE 47

#define FPS 100000 // microseconds

struct termios old_term;

bool QUIT = false;

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

    clrscr();

    struct winsize w;
    ioctl(1, TIOCGWINSZ, &w);
    cur_size.first = w.ws_col;
    cur_size.second = w.ws_row;
}

TView::~TView()
{
    clrscr();
    tcsetattr(0, TCSANOW, &old_term);
}

void TView::setDrawer(drawer drawFunc) { drawAll = drawFunc; }
void TView::setKeyHandler(keyHandler keyHandler) { keyHandlerFunc = keyHandler; }

const coord TView::getCurSize() { return cur_size; };

void TView::draw() {}

void TView::run()
{
    struct pollfd arr;
    arr.fd = 0;
    arr.events = POLLIN;

    clrscr();
    drawBox();
    bool Looser = false;

    drawAll();

    while (!QUIT)
    {
        int n = poll(&arr, 1, 100);
        if (n == 1)
        {
            char keybuf[BUFSIZ];
            int size = read(0, keybuf, BUFSIZ);

            for (int i = 0; i < size; i++)
            {
                if (keybuf[i] == 'q')
                {
                    QUIT = true;
                    break;
                }
                else
                {
                    keyHandlerFunc(keybuf[i]);
                    Looser = drawAll();
                    if (Looser)
                    {
                        youLost();
                        QUIT = true;
                        usleep(FPS);
                        return;
                    }
                }
            }
        }
        else
        {
            //#if 1
            Looser = drawAll();
            if (Looser)
            {
                youLost();
                QUIT = true;
                usleep(FPS);
                return;
            }
            //#endif
        }
    }

    return;
}

void TView::draw(coord& rabbit)
{
    setcolor(FG_MAGENTA, BG_BLACK);

    gotoxy(rabbit.first, rabbit.second);
    putc('@');

    setcolor(FG_BLACK, BG_BLACK);
}

void TView::draw(Snake& snake)
{
    setcolor(snake.snake_color);

    auto head = snake.body.begin();
    gotoxy(*head);

    switch (snake.snake_direction)
    {
        case DIRECTION::UPWARD:
            putc('^');
            break;
        case DIRECTION::LEFT:
            putc('<');
            break;
        case DIRECTION::RIGHT:
            putc('>');
            break;
        case DIRECTION::DOWNWARD:
            putc('v');
            break;
        default:
            break;
    }

    if (snake.body.begin() != snake.body.end())
        head++;
    else
    {
        setcolor(FG_BLACK, BG_BLACK);
        return;
    }

    for (auto point = head; point != snake.body.end(); point++)
    {
        gotoxy(*point);
        putc('0');
    }

    setcolor(FG_BLACK, BG_BLACK);
}

void TView::clrPoint(coord& point)
{
    gotoxy(point);
    putc(' ');
}

void TView::youLost()
{
    clrscr();
    drawBox();
    gotoxy(cur_size.first/2 - 9, cur_size.second/2);
    setcolor(FG_MAGENTA, BG_WHITE);
    puts("YOU LOST! GOOD TRY!");
    usleep(100 * FPS);
    setcolor(FG_BLACK, BG_BLACK);
}

void TView::drawBox()
{
    setcolor(FG_GREEN, BG_BLUE);

    hline(cur_size.first, 1);
    hline(cur_size.first, cur_size.second);
    vline(cur_size.second, 1);
    vline(cur_size.second, cur_size.first);

    setcolor(FG_BLACK, BG_BLACK);
}

void TView::gotoxy(int x, int y)
{
    printf("\e[%d;%dH", y, x);
}

void TView::gotoxy(const coord& point)
{
    printf("\e[%d;%dH", point.second, point.first);
}

void TView::clrscr()
{
    std::cout << "\e[H\e[J" << std::flush;
}

void TView::putc(char c)
{
    std::cout << c << std::flush;
}

void TView::puts(const char* s)
{
    std::cout << s << std::flush;
}

void TView::setcolor(int color)
{
    printf("\e[%dm", color);
}

void TView::setcolor(int f_color, int b_color)
{
    printf("\e[%d;%dm", f_color, b_color);
}

void TView::setcolor(COLOR color)
{
    printf("\e[%dm", (int) color);
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

/*void TView::check_size()
{
    struct winsize w;
    ioctl(1, TIOCGWINSZ, &w);

    if ((cur_size.cols != w.ws_col - 1) || (cur_size.lines != w.ws_row - 1))
        clrscr();

    cur_size.cols = w.ws_col - 1;
    cur_size.lines = w.ws_row - 1;
}*/

/*void TView::UserInformation()
{
    setcolor(FG_GREEN, BG_BLACK);

    gotoxy(2, 2);
    puts("Score: 0");
}*/