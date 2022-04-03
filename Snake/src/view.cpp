#include "view.h"
#include "tview.h"
#include "gview.h"

View* View::obj = NULL;

View* View::getView(const char* value)
{
    if (obj)
    {
        return obj;
    }

    if ((value == NULL) || (std::string(value) == "text"))
    {
        obj = new TView();
    }
    else if (std::string(value) == "gui")
    {
        //obj = new GView();
    }
    else 
    {
        perror("INVALID ARG");
        return NULL;
    }
    return obj;
}
