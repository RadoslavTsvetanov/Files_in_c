#include "dynarr.h"
#include <stdio.h>
#include <stdlib.h>

#define ASSERT_MEMORY_ALLOC(PTR)              \
    if ((PTR) == NULL)                        \
    {                                         \
        printf("Error allocating memory \n"); \
        exit(1);                              \
    }

static void resize(DynamicArray *arr, int newsize)
{
    if (newsize > arr->capacity)
    {
        arr->capacity *= 2;
        arr->buffer = (Book *)realloc(arr->buffer, sizeof(Book) * arr->capacity);
        ASSERT_MEMORY_ALLOC(arr->buffer);
    }
    else if (newsize <= arr->capacity / 2)
    {
        arr->capacity /= 2;
        arr->buffer = (Book *)realloc(arr->buffer, sizeof(Book) * arr->capacity);
        ASSERT_MEMORY_ALLOC(arr->buffer);
    }
    arr->size = newsize;
}

DynamicArray init(unsigned int capacity)
{
    DynamicArray arr = {
        capacity : capacity,
        size : 0,
        buffer : NULL
    };

    arr.buffer = (Book *)calloc(arr.capacity, sizeof(Book));
    ASSERT_MEMORY_ALLOC(arr.buffer);

    return arr;
}

Book getel(DynamicArray *arr, int index)
{
    return arr->buffer[index];
}

void pushback(DynamicArray *arr, Book value)
{
    int newsize = arr->size + 1;
    resize(arr, newsize);
    arr->buffer[arr->size - 1] = value;
}

Book popback(DynamicArray *arr)
{
    pop(arr, arr->size - 1);
}

void push(DynamicArray *arr, int index, Book value)
{
    int newsize = arr->size + 1;
    resize(arr, newsize);
    for (int i = arr->size - 1; i > index; i--)
    {
        arr->buffer[i] = arr->buffer[i - 1];
    }
    arr->buffer[index] = value;
}

void pushfront(DynamicArray *arr, Book value)
{
    push(arr, 0, value);
}

void pop(DynamicArray *arr, int index)
{
    int newsize = arr->size - 1;
    // index - 6
    for (int i = index; i < arr->size - 1; i++)
    {
        arr->buffer[i] = arr->buffer[i + 1];
    }
    resize(arr, newsize);
}

void popfront(DynamicArray *arr)
{
    pop(arr, 0);
};

void releasedynarr(DynamicArray *arr)
{
    if (arr->buffer != NULL)
    {
        free(arr->buffer);
        arr->buffer = NULL;
    }
    arr->capacity = 0;
    arr->size = 0;
}
