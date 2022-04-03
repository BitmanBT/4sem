#include "main.h"

int main(int argc, char* argv[])
{
    View* view;

    if ((argv[1] == NULL) || (std::string(argv[1]) == "text"))
    {
        view = View::getView("text");
    }
    else
    {
        view = View::getView(argv[1]);
    }

    view->run();

    delete view;

    return 0;
}