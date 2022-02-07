#include "list.h"

int main()
{
	List* list = List_create();
	printf("We have created the list and now we want to initialize it.\n");
	List_init(list, 10);
	printf("That's it:\n");
	List_print(list);

	printf("Now we are going to add element 0 to the front\n");
	List_pushFront(list, 0);
	printf("That's it:\n");
	List_print(list);
	int front = List_popFront(list);
	printf("%d was removed from the front.\n", front);
	printf("That's it:\n");
	List_print(list);

	printf("Now we are going to add element 11 to the back\n");
	List_pushBack(list, 11);
	printf("That's it:\n");
	List_print(list);
	int back = List_popBack(list);
	printf("%d was removed from the back.\n", back);
	printf("That's it:\n");
	List_print(list);

	printf("Which node do you want to find?\n");
	int index;
	scanf("%d", &index);
	Node* node = List_getNode(list, index);
	printf("That's it: %d\n", node->data);

	printf("Where an what do you want to push?\n");
	int where; int what;
	scanf("%d %d", &where, &what);
	List_push(list, where, what);
	printf("That's it:\n");
	List_print(list);

	printf("What do you want to pop?\n");
	scanf("%d", &what);
	int answer = List_pop(list, what);
	printf("That's it: %d\n", answer);
	List_print(list);

	List_delete(list);

	printf("We have deleted the list.\n");

	return 0;
}