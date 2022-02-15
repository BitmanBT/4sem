#include "list.h"
#include <stdbool.h>
#include <assert.h>

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

bool comp(void* x, void* y, bool (*compType)(void*, void*))
{
	assert(x); assert(y);

	bool ifTrue = compType(x, y);

	return ifTrue;
}

void bubbleSort(List* list, methods* m)
{
	int i = 0, j = 0;
	Node* this; Node* another;

	for (i = 0; i < list->size - 1; i++)
	{
		for(j = 0; j < list->size - i - 1; j++)
		{
			this = (m->getNode)(list, j);
			another = (m->getNode)(list, j+1);
			if (comp(this->data, another->data, compDouble))
			{
				void* tmp = this->data;
				this->data = another->data;
				another->data = tmp;
			}
		}
	}
}

int main()
{
	methods* mInt = (methods*)malloc(sizeof(methods));
	List* listInt = List_create(mInt);

	int a[10] = {7, 8, 9, 0, 1, 2, 5, 4, 3, 6};
	(mInt->init)(listInt, a, 10, sizeof(int));
	printf("We have: ");
	(mInt->print)(listInt, printElemInt);

	bubbleSort(listInt, mInt);

	printf("Sorted: ");
	(mInt->print)(listInt, printElemInt);

	(mInt->delete)(listInt);

	methods* mDouble = (methods*)malloc(sizeof(methods));
	List* listDouble = List_create(mDouble);

	double b[10] = { 1.7, 1.8, 2.9, 0.0, 1.1, 1.2, 1.5, 1.4, 1.3, 1.6};
	(mDouble->init)(listDouble, b, 10, sizeof(double));
	printf("We have: ");
	(mDouble->print)(listDouble, printElemDouble);

	bubbleSort(listDouble, mDouble);

	printf("Sorted: ");
	(mDouble->print)(listDouble, printElemDouble);

	(mDouble->delete)(listDouble);
	
	return 0;
}