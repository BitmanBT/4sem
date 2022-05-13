#include "Container.h"

#include <assert.h>

typedef struct Node
{
	struct Node* prev;
	void* data;
	struct Node* next;
} Node;

typedef struct List
{
	size_t size;
	Node* head;
	Node* tail;
} List;

void List_init(Container* list, void* arr, size_t n, size_t size);
void List_delete(Container* list);
void List_pushBack(Container* list, void* data);
void* List_popBack(Container* list);
void* List_getValue(Container* cont, size_t index);
void List_setValue(Container* cont, size_t index, void* data);
void List_print(Container* list, void (*printElem)(void*));
void List_bubbleSort(Container* cont, bool (*compType)(void*, void*));

Container* List_create()
{
	Container* tmp = (Container*)malloc(sizeof(Container) + sizeof(List));
	if (tmp == NULL)
		exit(1);
	tmp->m = malloc(sizeof(methods));
	if (tmp->m == NULL)
	{
		free(tmp);
		exit(2);
	}
	List* list = (List*)(tmp + 1);
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;

	tmp->m->init = List_init;
	tmp->m->delete = List_delete;
	tmp->m->pushBack = List_pushBack;
	tmp->m->popBack = List_popBack;
	tmp->m->getValue = List_getValue;
	tmp->m->setValue = List_setValue;
	tmp->m->print = List_print;
	tmp->m->bubbleSort = List_bubbleSort;

	return tmp;
}

void List_delete(Container* cont)
{
	List* list = (List*)(cont + 1);
	
	Node* tmp = list->head;
	Node* next = NULL;

	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}

	free(cont);
}

void List_pushBack(Container* cont, void* data)
{
	List* list = (List*)(cont + 1);
	
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
		exit(5);

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

void* List_popBack(Container* cont)
{
	List* list = (List*)(cont + 1);
	
	Node* next; void* tmp;
	if (list->tail == NULL)
		exit(6);

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

void* List_getNode(Container* cont, size_t index)
{
	List* list = (List*)(cont + 1);
	
	Node* tmp = list->head;
	size_t i = 0;

	while (tmp && (i < index))
	{
		tmp = tmp->next;
		i++;
	}

	return tmp;
}

void* List_getValue(Container* cont, size_t index)
{
	List* list = (List*)(cont + 1);

	Node* elem = list->head;
	int i = 0;

	while ((elem) && (i < index))
	{
		elem = elem->next;
		i++;
	}

	return elem->data;
}

void List_setValue(Container* cont, size_t index, void* data)
{
	List* list = (List*)(cont + 1);

	Node* elem = list->head;
	int i = 0;

	while ((elem) && (i < index))
	{
		elem = elem->next;
		i++;
	}

	elem->data = data;
}

void List_print(Container* cont, void (*printElem)(void*))
{
	List* list = (List*)(cont + 1);
	
	Node* tmp = list->head;

	while (tmp)
	{
		printElem(tmp->data);
		tmp = tmp->next;
	}

	printf("\n");
}

void List_init(Container* cont, void* arr, size_t n, size_t size)
{
	List* list = (List*)(cont + 1);
	
	size_t i = 0;

	if (arr == NULL)
		exit(6);
	if (list == NULL)
		exit(7);

	while (i < n)
	{
		List_pushBack(cont, (char*)arr + i*size);
		i++;
	}
}

void List_bubbleSort(Container* cont, bool (*compType)(void*, void*))
{
	List* list = (List*)(cont + 1);

	int i = 0, j = 0;
	Node* this; Node* another;

	for (i = 0; i < list->size - 1; i++)
	{
		for (j = 0; j < list->size - i - 1; j++)
		{
			this = List_getNode(cont, j);
			another = List_getNode(cont, j + 1);
			if (compType(this->data, another->data))
			{
				void* tmp = this->data;
				this->data = another->data;
				another->data = tmp;
			}
		}
	}
}