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
	Container* listInt = List_create();

	int a[10] = {7, 8, 9, 0, 1, 2, 5, 4, 3, 6};
	(listInt->m->init)(listInt, a, 10, sizeof(int));
	printf("We have: ");
	(listInt->m->print)(listInt, printElemInt);

	(listInt->m->bubbleSort)(listInt, compInt);

	printf("Sorted: ");
	(listInt->m->print)(listInt, printElemInt);

	(listInt->m->delete)(listInt);

	Container* listDouble = List_create();

	double b[10] = { 1.7, 1.8, 2.9, 0.0, 1.1, 1.2, 1.5, 1.4, 1.3, 1.6};
	(listDouble->m->init)(listDouble, b, 10, sizeof(double));
	printf("We have: ");
	(listDouble->m->print)(listDouble, printElemDouble);

	(listDouble->m->bubbleSort)(listDouble, compDouble);

	printf("Sorted: ");
	(listDouble->m->print)(listDouble, printElemDouble);

	(listDouble->m->delete)(listDouble);
	
	return 0;
}