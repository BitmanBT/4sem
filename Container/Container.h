#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct methods
{
    void (*init)(void*, void*, size_t, size_t);
    void (*delete)(void*);

    void (*pushBack)(void*, void*);
    void* (*popBack)(void*);
    void (*print)(void*, void (*printElem)(void*));
    void (*bubbleSort)(void*, bool (*compType)(void*, void*));
    void* (*getValue) (void*, size_t);
    void (*setValue) (void*, size_t, void*);
} methods;

typedef struct Container
{
    methods* m;
} Container;

Container* List_create();
Container* vector_create();

#endif // CONTAINER_H