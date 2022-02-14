#include "list.h"

List* List_create(methods* m)
{
	List* tmp = (List*)malloc(sizeof(List));
	tmp->size = 0;
	tmp->head = NULL;
	tmp->tail = NULL;

	m->init = List_init;
	m->delete = List_delete;
	m->pushFront = List_pushFront;
	m->popFront = List_popFront;
	m->pushBack = List_pushBack;
	m->popBack = List_popBack;
	m->push = List_push;
	m->pop = List_pop;
	m->getNode = List_getNode;
	m->print = List_print;

	return tmp;
}

void List_delete(List* list)
{
	Node* tmp = list->head;
	Node* next = NULL;

	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}

	free(list);
	list = NULL;
}

void List_pushFront(List* list, void* data)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
		exit(1);

	tmp->data = data;
	tmp->prev = NULL;
	tmp->next = list->head;

	if (list->head)
		list->head->prev = tmp;
	list->head = tmp;

	if (list->tail == NULL)
		list->tail = tmp;

	list->size++;
}

void* List_popFront(List* list)
{
	Node* prev; void* tmp;
	if (list->head == NULL)
		exit(2);

	prev = list->head;
	list->head = list->head->next;
	if (list->head)
		list->head->prev = NULL;

	if (prev == list->tail)
		list->tail = NULL;

	tmp = prev->data;
	free(prev);

	list->size--;
	return tmp;
}

void List_pushBack(List* list, void* data)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
		exit(3);

	tmp->data = data;
	tmp->prev = list->tail;
	tmp->next = NULL;

	if (list->tail)
		list->tail->next = tmp;
	list->tail = tmp;

	if (list->head == NULL)
		list->head = tmp;

	list->size++;
}

void* List_popBack(List* list)
{
	Node* next; void* tmp;
	if (list->tail == NULL)
		exit(4);

	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail)
		list->tail->next = NULL;

	if (next == list->head)
		list->head = NULL;

	tmp = next->data;
	free(next);

	list->size--;
	return tmp;
}

Node* List_getNode(List* list, size_t index)
{
	Node* tmp = list->head;
	size_t i = 0;

	while (tmp && (i < index))
	{
		tmp = tmp->next;
		i++;
	}

	return tmp;
}

void List_push(List* list, size_t index, void* data)
{
	Node* elem; Node* tmp;
	elem = List_getNode(list, index);
	if (elem == NULL)
		exit(5);

	tmp = (Node*)malloc(sizeof(Node));
	tmp->data = data;
	tmp->prev = elem;
	tmp->next = elem->next;

	if (elem->next)
		elem->next->prev = tmp;
	elem->next = tmp;

	if (!elem->prev)
		list->head = elem;
	if (!elem->next)
		list->tail = elem;

	list->size++;
}

void* List_pop(List* list, size_t index)
{
	Node* elem; void* tmp;
	elem = List_getNode(list, index);
	if (elem == NULL)
		exit(5);

	if (elem->prev)
		elem->prev->next = elem->next;
	if (elem->next)
		elem->next->prev = elem->prev;
	tmp = elem->data;

	if (!elem->prev)
		list->head = elem->next;
	if (!elem->next)
		list->tail = elem->prev;

	free(elem);

	list->size--;

	return tmp;
}

void List_print(List* list, void (*printElem)(void*))
{
	Node* tmp = list->head;

	while (tmp)
	{
		printElem(tmp->data);
		tmp = tmp->next;
	}

	printf("\n");
}

void List_init(List* list, void* arr, size_t n, size_t size)
{
	size_t i = 0;

	if (arr == NULL)
		exit(6);
	if (list == NULL)
		exit(7);

	while (i < n)
	{
		List_pushBack(list, (char*)arr + i*size);
		i++;
	}
}