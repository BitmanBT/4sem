#include "Container.h"

void printElemInt(void* x)
{
    printf("%d ", *((int*)x));
}

void printElemDouble(void* x)
{
    printf("%0.1f ", *((double*)x));
}

bool compInt(void* x, void* y)
{
    if ((*(int*)x) > (*(int*)y))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool compDouble(void* x, void* y)
{
    if ((*(double*)x) > (*(double*)y))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    Container* vectorInt = vector_create();

    int a[10] = { 7, 8, 9, 0, 1, 2, 5, 4, 3, 6 };
    (vectorInt->m->init)(vectorInt, a, 10, sizeof(int));
    printf("We have: ");
    (vectorInt->m->print)(vectorInt, printElemInt);

    (vectorInt->m->bubbleSort)(vectorInt, compInt);

    printf("Sorted: ");
    (vectorInt->m->print)(vectorInt, printElemInt);

    (vectorInt->m->delete)(vectorInt);

    Container* vectorDouble = vector_create();

    double b[10] = { 1.7, 1.8, 2.9, 0.0, 1.1, 1.2, 1.5, 1.4, 1.3, 1.6 };
    (vectorDouble->m->init)(vectorDouble, b, 10, sizeof(double));
    printf("We have: ");
    (vectorDouble->m->print)(vectorDouble, printElemDouble);

    (vectorDouble->m->bubbleSort)(vectorDouble, compDouble);

    printf("Sorted: ");
    (vectorDouble->m->print)(vectorDouble, printElemDouble);

    (vectorDouble->m->delete)(vectorDouble);

    return 0;
}