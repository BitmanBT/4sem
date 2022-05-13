#include "Container.h"

void printElem(void* x)
{
    printf("%d ", *((int*)x));
}

int main()
{
    Container* container;
    container = vector_create();
    printf("We have created the vector and now we want to initialize it.\n");

    int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    (container->m->init)(container, a, 10, sizeof(int));
    printf("That's it:\n");
    (container->m->print)(container, printElem);

    int twenty = 20;
    printf("Now we are going to set 5th element as 20\n");
    (container->m->setValue)(container, 5, &twenty);
    printf("That's it:\n");
    (container->m->print)(container, printElem);

    int ten = 10;
    printf("Now we are going to add element 10 to the back\n");
    (container->m->pushBack)(container, &ten);
    printf("That's it:\n");
    (container->m->print)(container, printElem);

    int* back = (container->m->popBack)(container);
    printf("%d was removed from the back.\n", *back);
    printf("That's it:\n");
    (container->m->print)(container, printElem);

    printf("Which node do you want to find?\n");
    int index;
    scanf("%d", &index);
    void* value = (container->m->getValue)(container, index);
    printf("That's it: %d\n", *((int*)(value)));

    (container->m->delete)(container);
    printf("We have deleted the vector.\n");

    return 0;
}