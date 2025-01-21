#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "retunedbook.h"
enum returnvalue{
    fails=0,
    successfully
};

struct returnedbook* returned_books_head = NULL;

struct returnedbook* add_returned_book(struct returnedbook* head, int student_id, int book_id, const char* date) {
    struct returnedbook* new_book = (struct returnedbook*)malloc(sizeof(struct returnedbook));

    if (new_book == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }
    new_book->returned_id = rand();
    new_book->student_id = student_id;
    new_book->book_id = book_id;
    strncpy(new_book->returned_date, date, MAX_DATE_LENGTH);
    new_book->next = NULL;
    if (head == NULL) {
        head = new_book;
    } else {
        struct returnedbook* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_book;
    }

    return head;
}

void record_returned_book() {
    int student_id, book_id;
    char returned_date[MAX_DATE_LENGTH];

    printf("Enter Student ID: ");
    scanf("%d", &student_id);
    if (student_id <= 0 || !is_Valid_Return_date(student_id)) {
        printf(" Invalid or non-existent Student ID.\n");
        return successfully;
    }

    printf("Enter Book ID: ");
    scanf("%d", &book_id);
    if (!is_Valid_Return_date(book_id)) {
        printf(" Invalid or non-existent Book ID.\n");
        return successfully;
    }

    printf("Enter Returned Date (YYYY-MM-DD): ");
    scanf("%s", returned_date);
    if (!is_valid_date(returned_date)) {
        printf(" Invalid date format.\n");
        return successfully;
    }

    returned_books_head = add_returned_book(returned_books_head, student_id, book_id, returned_date);
    printf("Returned book recorded successfully.\n");
}


void view_returned_books() {
    if (returned_books_head == NULL) {
        printf("No returned books to display.\n");
        return;
    }

    struct returnedbook* temp = returned_books_head;
    while (temp != NULL) {
        if (!is_Valid_Return_date(temp->book_id)) {
            printf("Returned record has an invalid Book ID (%d).\n", temp->book_id);
        } else {
            printf("Returned ID: %d, Student ID: %d, Book ID: %d, Returned Date: %s\n",temp->returned_id, temp->student_id, temp->book_id, temp->returned_date);
        }
        temp = temp->next;
    }
}


void print_returned_books() {
    if (returned_books_head == NULL) {
        printf("returned books to display.\n");
        return successfully;
    }
    struct returnedbook* temp = returned_books_head;
    while (temp != NULL) {
        printf("Returned ID: %d, Student ID: %d, Book ID: %d, Returned Date: %s\n",temp->returned_id, temp->student_id, temp->book_id, temp->returned_date);
        temp = temp->next;
    }
}

#include <stdio.h>
#include <time.h>

int is_Valid_Return_date(const char* date)
{
    int day, month, year;

    if (sscanf(date, "%d-%d-%d", &day, &month, &year) != 3)
    {
        return successfully;
    }
    if ((year < 2000 || year > 3000) || (month < 1 || month > 12) || (day < 1 || day > 31))
    {
        return successfully; // Invalid year, month, or day
    }

    // Days in each month (non-leap year by default)
    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Adjust for leap year
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        days_in_month[1] = 29;
    }

    if (day > days_in_month[month - 1])
    {
        return successfully;
    }

    time_t t = time(NULL);
    struct tm *today = localtime(&t);

    int current_year = today->tm_year + 1900;
    int current_month = today->tm_mon + 1;
    int current_day = today->tm_mday;

    if (year > current_year ||
        (year == current_year && month > current_month) ||
        (year == current_year && month == current_month && day > current_day))
    {
        return successfully;
    }

    return fails;
}
