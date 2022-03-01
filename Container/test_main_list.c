#include "Container.h"

void printElem(void* x)
{
	printf("%d ", *((int*) x));
}

int main()
{
	Container* list = List_create();
	printf("We have created the list and now we want to initialize it.\n");

	int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	(list->m->init)(list, a, 10, sizeof(int));
	printf("That's it:\n");
	(list->m->print)(list, printElem);

	int ten = 10;
	printf("Now we are going to add element 10 to the back\n");
	(list->m->pushBack)(list, &ten);
	printf("That's it:\n");
	(list->m->print)(list, printElem);

	int* back = (list->m->popBack)(list);
	printf("%d was removed from the back.\n", *back);
	printf("That's it:\n");
	(list->m->print)(list, printElem);

	printf("Enter, where and what do you want to set:\n");
	int to_set, where_to_set;
	scanf("%d %d", &where_to_set, &to_set);
	(list->m->setValue)(list, where_to_set, &to_set);
	printf("That's it:\n");
	(list->m->print)(list, printElem);

	printf("Enter what do you want to get:\n");
	int where_to_get;
	scanf("%d", &where_to_get);
	int* got = (list->m->getValue)(list, where_to_get);
	printf("That's it: %d\n", (int)*got);

	(list->m->delete)(list);

	printf("We have deleted the list.\n");

	return 0;
}