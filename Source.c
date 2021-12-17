#define _CRT_SECURE_NO_WARNINGS
#define n 8
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct library
{
    char author[20];
    char name[20];
    int year;
    int pages;
    int cost;
    struct library* next;
}book;


void print_books(book*);
void scan_books(FILE* file, book** head);
void insert_book(book** head, book* new_book);
void remove_book(book** head, book* node);
void remove_small_books(book** head);
void free_library(book** head);


int main()
{
    FILE* file;
    file = fopen("file.txt", "r");
    book* head = NULL;

    scan_books(file, &head);
    printf("Books:");
    print_books(head);

    remove_small_books(&head);
    print_books(head);

    free_library(&head);

    fclose(file);
}

void print_books(book* head) {
    printf("\n");
    book* current = head;
    while (current)
    {
        printf("%s %s %d %d %d\n", current->author, current->name,
            current->year, current->pages, current->cost);
        current = current->next;
    }
    printf("\n");
}

void scan_books(FILE* file, book** head) {
    book* node;
    for (int i = 0; i < n; i++) {
        node = (book*)malloc(sizeof(book));
        if (!node)
        {
            return;
        }
        node->next = NULL;
        if(!fscanf(file, "%s %s %d %d %d", node->author, node->name,
            &node->year, &node->pages, &node->cost))
            return;
        insert_book(head, node);
    }
}

void insert_book(book** head, book* new_book)
{
    if (!*head || strcmp((*head)->author, new_book->author) < 0)
    {
        new_book->next = *head;
        *head = new_book;
        return;
    }

    book* current = *head;
    while (current->next && strcmp(current->next->author, new_book->author) > 0)
    {
        current = current->next;
    }
    new_book->next = current->next;
    current->next = new_book;
}
void remove_book(book** head, book* node)
{
    if (!*head || !node)
        return;
    book* temp = NULL;

    if (*head == node)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    book* current = *head;
    while (current)
    {
        if (current->next == node)
        {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

void remove_small_books(book** head)
{
    book* current = *head;
    
    while (current)
    {
        if (current->pages < 50)
        {
            book* temp = current->next;
            remove_book(head, current);
            current = temp;
            continue;
        }
        current = current->next;
    }
}

void free_library(book** head)
{
    book* current = *head;
    while (current)
    {
        book* temp = current;
        current = current->next;
        free(temp);
    }
}