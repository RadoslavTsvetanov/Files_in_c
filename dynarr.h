#ifndef DYNARR_H
#define DYNARR_H

typedef struct
{
    char name[100];
    char author[100];
    char type[100];
    char creation_year[100];
    char ISBN[100];
} Book;

typedef struct
{
    Book *buffer;
    unsigned int capacity;
    unsigned int size;
} DynamicArray;

DynamicArray init(unsigned int capacity);

Book getel(DynamicArray *arr, int index);

void pushback(DynamicArray *arr, Book value);

Book popback(DynamicArray *arr);

void push(DynamicArray *arr, int index, Book value);

void pushfront(DynamicArray *arr, Book value);

// For homework
void pop(DynamicArray *arr, int index);

// For homework
void popfront(DynamicArray *arr);

void releasedynarr(DynamicArray *arr);

#endif