#include <stdio.h>
#include <stdlib.h>
#include "dynarr.h"
#include <string.h>

void delete_book(DynamicArray *arr, const char *isbn)
{
    for (int i = 0; i < arr->size; i++)
    {
        if (strcmp(isbn, arr->buffer[i].ISBN) == 0)
        {
            pop(arr, i);
            return;
        }
    }
    printf("Book with ISBN %s not found.\n", isbn);
}

void add_book(DynamicArray *arr, const char *name, const char *author, const char *type, const char *creation_year, const char *isbn)
{
    Book book;
    strcpy(book.name, name);
    strcpy(book.author, author);
    strcpy(book.type, type);
    strcpy(book.creation_year, creation_year);
    strcpy(book.ISBN, isbn);

    pushfront(arr, book);
}

void print_dynarr(DynamicArray *arr)
{
    for (int i = 0; i < arr->size; i++)
    {
        const Book *book = &(arr->buffer[i]);

        printf("Book %d:\n", i + 1);
        printf("Name: %s\n", book->name);
        printf("Author: %s\n", book->author);
        printf("Type: %s\n", book->type);
        printf("Creation Year: %s\n", book->creation_year);
        printf("ISBN: %s\n", book->ISBN);

        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    DynamicArray books = init(1);
    FILE *f = fopen("books.txt", "r");
    char line[256];
    while (fgets(line, sizeof(line), f) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        char *token;
        char *tokens[5];
        int token_num = 0;

        token = strtok(line, ",");
        while (token != NULL)
        {
            tokens[token_num++] = token;
            token = strtok(NULL, ",");
        }
        Book book;
        strcpy(book.name, tokens[0]);
        strcpy(book.author, tokens[1]);
        strcpy(book.creation_year, tokens[3]);
        strcpy(book.type, tokens[2]);
        strcpy(book.ISBN, tokens[4]);
        pushfront(&books, book);
    }
    fclose(f);

    if (argc > 1)
    {
        int choice = atoi(argv[1]);
        if (choice == 1)
        {
            print_dynarr(&books);
        }
        else if (choice == 2)
        {
            add_book(&books, argv[2], argv[3], argv[4], argv[5], argv[6]);
        }
        else if (choice == 3)
        {
            delete_book(&books, argv[2]);
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    FILE *f_1 = fopen("books.txt", "w");
    for (int i = 0; i < books.size; i++)
    {
        Book *book = &(books.buffer[i]);
        fprintf(f_1, "%s,", book->name);
        fprintf(f_1, "%s,", book->author);
        fprintf(f_1, "%s,", book->type);
        fprintf(f_1, "%s,", book->creation_year);
        fprintf(f_1, "%s,", book->ISBN);
        fprintf(f_1, "\n");
    }
    fclose(f_1);

    return 0;
}
