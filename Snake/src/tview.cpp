#include "../include/tview.h"

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

const size_t num_rabbits = 10;

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

        struct pollfd arr;
        arr.fd = 0;
        arr.events = POLLIN;

        int n = poll(&arr, 1, 500);
        if (n == 1)
        {
            char c;
            scanf("%c", &c);

            if (c == 'q') break;
        }

        usleep(FPS);
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

    UserInformation();

    box(&cur_size);

    std::list<rabbit> rabbits;

    for (int i = 0; i < num_rabbits; i++)
    {
        std::pair<int, int> tmp = RandCoord(cur_size.cols, cur_size.lines);
        rabbits.push_back(tmp);
    }

    DrawRabbits(rabbits);

    gotoxy(w.ws_col, w.ws_row);
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
    setcolor(FG_GREEN, BG_BLUE);
    
    hline(cur_size->cols, 1);
    hline(cur_size->cols, cur_size->lines);
    vline(cur_size->lines, 1);
    vline(cur_size->lines, cur_size->cols);
}

void TView::UserInformation()
{
    setcolor(FG_GREEN, BG_BLACK);
    
    gotoxy(2, 2);
    puts("Score: 0");
}

std::pair<int, int> TView::RandCoord(const size_t cols, const size_t lines)
{
    std::pair<int, int> rand_coord;

    std::random_device random_device;
    std::mt19937 generator(random_device());

    std::uniform_int_distribution<> distribution_x(2, cols - 1);
    std::uniform_int_distribution<> distribution_y(2, lines - 1);

    int x = distribution_x(generator);
    int y = distribution_y(generator);

    rand_coord.first = x;
    rand_coord.second = y;

    return rand_coord;
}

void TView::DrawRabbits(const std::list<rabbit>& rabbits)
{
    setcolor(FG_MAGENTA, BG_BLACK);

    for (const auto [x, y] : rabbits)
    {
        gotoxy(x, y);
        putc('@');
    }
}