#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

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

typedef struct Container
{
	List list;
} Container;

typedef struct methods
{
	void (*init)(void*, void*, size_t, size_t);
	void (*delete)(void*);

	void (*pushFront)(void*, void*);
	void* (*popFront)(void*);
	void (*pushBack)(void*, void*);
	void* (*popBack)(void*);
	void (*push)(void*, size_t, void*);
	void* (*pop)(void*, size_t);
	Node* (*getNode)(void*, size_t);
	void (*print)(void*, void (*printElem)(void*));
} methods;

List* List_create(methods* m);

void List_init(List* list, void* arr, size_t n, size_t size);
void List_delete(List* list);
void List_pushFront(List* list, void* data);
void* List_popFront(List* list);
void List_pushBack(List* list, void* data);
void* List_popBack(List* list);
void List_push(List* list, size_t index, void* data);
void* List_pop(List* list, size_t index);
Node* List_getNode(List* list, size_t index);
void List_print(List* list, void (*printElem)(void*));

#endif // LIST_H