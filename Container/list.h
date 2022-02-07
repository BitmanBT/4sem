#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
	struct Node* prev;
	int data;
	struct Node* next;
} Node;

typedef struct List
{
	size_t size;
	Node* head;
	Node* tail;
} List;

List* List_create();
void List_delete(List* list);
void List_pushFront(List* list, int data);
int List_popFront(List* list);
void List_pushBack(List* list, int data);
int List_popBack(List* list);
Node* List_getNode(List* list, size_t index);
void List_push(List* list, size_t index, int data);
int List_pop(List* list, size_t index);
void List_print(List* list);
void List_init(List* list, size_t n);

#endif // LIST_H