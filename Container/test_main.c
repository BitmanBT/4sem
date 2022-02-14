#include "list.h"

void printElem(void* x)
{
	printf("%d ", *((int*) x));
}

int main()
{
	methods* m = (methods*)malloc(sizeof(methods));
	Container* list = List_create(m);
	printf("We have created the list and now we want to initialize it.\n");

	int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	(m->init)(list, a, 10, sizeof(int));
	printf("That's it:\n");
	(m->print)(list, printElem);

	int zero = 0;
	printf("Now we are going to add element 0 to the front\n");
	(m->pushFront)(list, &zero);
	printf("That's it:\n");
	(m->print)(list, printElem);

	int* front = (m->popFront)(list);
	printf("%d was removed from the front.\n", *front);
	printf("That's it:\n");
	(m->print)(list, printElem);

	int ten = 10;
	printf("Now we are going to add element 10 to the back\n");
	(m->pushBack)(list, &ten);
	printf("That's it:\n");
	(m->print)(list, printElem);

	int* back = (m->popBack)(list);
	printf("%d was removed from the back.\n", *back);
	printf("That's it:\n");
	(m->print)(list, printElem);

	printf("Which node do you want to find?\n");
	int index;
	scanf("%d", &index);
	Node* node = (m->getNode)(list, index);
	printf("That's it: %d\n", *((int*)(node->data)));

	printf("Where an what do you want to push?\n");
	int where; int what;
	scanf("%d %d", &where, &what);
	(m->push)(list, where, &what);
	printf("That's it:\n");
	(m->print)(list, printElem);

	printf("What do you want to pop?\n");
	int pop_what;
	scanf("%d", &pop_what);
	int* answer = (m->pop)(list, pop_what);
	printf("That's it: %d\n", *answer);
	(m->print)(list, printElem);

	(m->delete)(list);

	printf("We have deleted the list.\n");

	return 0;
}