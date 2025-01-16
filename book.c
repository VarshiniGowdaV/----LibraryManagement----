
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

struct book* book_head = NULL;

struct book* add_book(struct book* book_head, char* name, char* title, int book_id, char* author)
{
    struct book* new_book = (struct book*)malloc(sizeof(struct book));
    if (!new_book)
    {
        printf("Memory allocation failed!\n");
        return book_head;
    }
    new_book->book_id = book_id;
    strncpy(new_book->name, name, MAX_NAME_LENGTH);
    strncpy(new_book->author, author, MAX_AUTHOR_LENGTH);
    strncpy(new_book->title, title, MAX_TITLE_LENGTH);
    new_book->total_copies = 0;
    new_book->available_copies = 0;
    new_book->deleted = 0;
    new_book->next = NULL;
    if (book_head == NULL) {
        book_head = new_book;
    } else {
        struct book* current = book_head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_book;
    }

    return book_head;
}
void update_book() {
    int book_id;
    printf("Enter book ID to update: ");
    scanf("%d", &book_id);

    struct book* current = book_head;
    while (current != NULL) {
        if (current->book_id == book_id) {
            printf("Enter new book name: ");
            getchar();
            fgets(current->name, MAX_NAME_LENGTH, stdin);
            current->name[strcspn(current->name, "\n")] = '\0';

            printf("Enter new author name: ");
            fgets(current->author, MAX_AUTHOR_LENGTH, stdin);
            current->author[strcspn(current->author, "\n")] = '\0';

            printf("Enter new book title: ");
            fgets(current->title, 100, stdin);
            current->title[strcspn(current->title, "\n")] = '\0';

            printf("Enter new total copies: ");
            scanf("%d", &current->total_copies);
            current->available_copies = current->total_copies;

            printf("Book updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Book with ID %d not found.\n", book_id);
}

void delete_book() {
    int book_id;
    printf("Enter book ID to delete: ");
    scanf("%d", &book_id);

    struct book* current = book_head;
    struct book* prev = NULL;

    while (current != NULL) {
        if (current->book_id == book_id) {
            current->deleted = 1;
            printf("Book with ID %d marked as deleted.\n", book_id);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Book with ID %d not found.\n", book_id);
}

void remove_book(int book_id) {
    struct book* current = book_head;
    struct book* prev = NULL;

    while (current != NULL) {
        if (current->book_id == book_id) {
            if (prev == NULL) {
                book_head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Book with ID %d deleted from list.\n", book_id);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Book with ID %d not found.\n", book_id);
}
struct book* search_book_by_id(int book_id) {
    struct book* current = book_head;
    while (current != NULL) {
        if (current->book_id == book_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
struct book* search_book() {
    char search_term[MAX_NAME_LENGTH];
    printf("Enter book name or author to search: ");
    getchar();
    fgets(search_term, MAX_NAME_LENGTH, stdin);
    search_term[strcspn(search_term, "\n")] = '\0';

    struct book* current = book_head;
    while (current != NULL) {
        if (strstr(current->name, search_term) != NULL || strstr(current->author, search_term) != NULL) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
void display_books() {
    struct book* current = book_head;
    if (current == NULL) {
        printf("No books available.\n");
        return;
    }

    printf("List of books:\n");
    while (current != NULL) {
        if (current->deleted == 0) {
            printf("ID: %d, Name: %s, Author: %s, Title: %s, Total Copies: %d, Available Copies: %d\n",
                   current->book_id, current->name, current->author, current->title, current->total_copies, current->available_copies);
        }
        current = current->next;
    }
}
