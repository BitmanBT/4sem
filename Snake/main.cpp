#include <cstdio>
#include "view.h"
#include "model.h"
#include <string>

int main(int argc, char* argv[])
{
    View* v;

    if ((argv[1] == NULL) || (std::string(argv[1]) == "text"))
    {
        v = View::getView("text");
    }
    else
    {
        v = View::getView(argv[1]);
    }

    v->run();

    return 0;
}