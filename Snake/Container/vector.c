#include "Container.h"

typedef struct Node
{
    size_t num;
    void* data;
} Node;


typedef struct Vector
{
    Node* first;
    size_t size;
} Vector;

void vector_pushBack(Container* container, void* data);
void* vector_popBack(Container* container);
void vector_init(Container* container, void* arr, size_t n, size_t size);
void vector_delete(Container* container);
void vector_print(Container* container, void (*printElem)(void*));
void vector_bubbleSort(Container* container, bool (*compType)(void*, void*));
void vector_setValue(Container* container, size_t index, void* data);
void* vector_getValue(Container* container, size_t index);

Container* vector_create()
{
    Container* container = malloc(sizeof(Container) + sizeof(Vector));
    if (container == NULL)
        exit(1);
    container->m = malloc(sizeof(methods));
    if (container->m == NULL) {
        free(container);
        exit(2);
    }
    Vector* vector = (Vector*)(container + 1);
    vector->first = NULL;
    vector->size = 0;

    container->m->pushBack = vector_pushBack;
    container->m->popBack = vector_popBack;
    container->m->init = vector_init;
    container->m->delete = vector_delete;
    container->m->print = vector_print;
    container->m->bubbleSort = vector_bubbleSort;
    container->m->getValue = vector_getValue;
    container->m->setValue = vector_setValue;
    return container;
}

void vector_pushBack(Container* container, void* data)
{
    Vector* vector = (Vector*)(container + 1);
    ++(vector->size);
    Node* elem = (Node*)malloc(sizeof(Node));
    if (vector->first == NULL)
    {
        elem->data = data;
        elem->num = 0;
        vector->first = elem;
    }
    else
    {
        elem = vector->first + (vector->size - 1) * sizeof(Node*);
        elem->data = data;
        elem->num = vector->size - 1;
    }
}

void* vector_popBack(Container* container)
{
    Vector* vector = (Vector*)(container + 1);
    Node* elem = (Node*)malloc(sizeof(Node));
    void* tmp;
    elem = vector->first + (vector->size - 1) * sizeof(Node*);
    tmp = elem->data;
    elem = NULL;
    --(vector->size);
    return tmp;
}

void vector_setValue(Container* container, size_t index, void* data)
{
    Vector* vector = (Vector*)(container + 1);
    if (index >= vector->size)
        exit(3);
    Node* elem = vector->first + sizeof(Node*) * index;
    elem->data = data;
    elem->num = index;
}

void* vector_getValue(Container* container, size_t index)
{
    Vector* vector = (Vector*)(container + 1);
    Node* elem = vector->first + sizeof(Node*) * index;
    return elem->data;
}

void vector_init(Container* container, void* arr, size_t n, size_t size)
{
    Vector* vector = (Vector*)(container + 1);
    size_t i = 0;
    if (arr == NULL)
        exit(4);
    if (vector == NULL)
        exit(5);
    while (i < n)
    {
        vector_pushBack(container, (char*)arr + i * size);
        i++;
    }
}

void vector_delete(Container* container)
{
    Vector* vector = (Vector*)(container + 1);
    free(vector->first);
    vector->first = NULL;
    free(container);
    vector = NULL;
}

void vector_print(Container* container, void (*printElem)(void*))
{
    Vector* vector = (Vector*)(container + 1);
    size_t i = 0;
    void* data = vector_getValue(container, i);
    printElem(data);
    while ((data) && (i + 1 < vector->size))
    {
        ++i;
        data = vector_getValue(container, i);
        printElem(data);
    }
    printf("\n");
}

void vector_bubbleSort(Container* container, bool (*compType)(void*, void*))
{
    Vector* vector = (Vector*)(container + 1);
    int i = 0, j = 0;
    Node* this; Node* another;
    for (i = 0; i < vector->size - 1; i++)
    {
        for (j = 0; j < vector->size - i - 1; j++)
        {
            this = vector->first + sizeof(Node*) * j;
            another = vector->first + sizeof(Node*) * (j + 1);
            if (compType(this->data, another->data))
            {
                void* tmp = this->data;
                this->data = another->data;
                another->data = tmp;
            }
        }
    }
}

