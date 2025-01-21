#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "borrowedbook.h"
#include "book.h"
#include "student.h"
enum retunvalue
{
    fails=0,
    successfully
};

struct borrowedbook* borrowedbook_head = NULL;
void record_borrowed_book(void)
{
    int student_id, book_id;
    char borrowed_date[20];

    printf("Enter student ID: ");
    scanf("%d", &student_id);


    if (student_id <= 0 || !is_valid_date(student_id))
    {
        printf("Invalid student ID.\n");
        return fails ;
    }

    printf("Enter book ID: ");
    scanf("%d", &book_id);

    printf("Enter borrowed date (DD-MM-YYYY): ");
    scanf("%s", borrowed_date);

    if (!is_valid_date(borrowed_date))
    {
        printf(" Invalid date format.\n");
        return  fails;
    }

    borrowedbook_head = add_borrowed_book(borrowedbook_head, student_id, book_id, borrowed_date);
    printf("The book has been recorded as borrowed.\n");
}

void view_borrowed_books(void)
{
    struct borrowedbook* current = borrowedbook_head;
    if (current == NULL)
    {
        printf("No borrowed books available.\n");
        return fails;
    }
    printf("Student ID | Book ID | Borrowed Date\n");
    while (current != NULL)
    {
        printf("%d | %d | %s\n", current->student_id, current->book_id, current->borrowed_date);
        current = current->next;
    }
}

struct borrowedbook* add_borrowed_book(struct borrowedbook* head, int student_id, int book_id, const char* borrowed_date)
{
    struct borrowedbook* new_book = (struct borrowedbook*)malloc(sizeof(struct borrowedbook));
    new_book->student_id = student_id;
    new_book->book_id = book_id;
    strncpy(new_book->borrowed_date, borrowed_date, MAX_DATE_LENGTH);
    new_book->next = NULL;

    if (head == NULL)
    {
        return new_book;
    }
    else
    {
        struct borrowedbook* current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_book;
    }
    save_Book_To_File();
    return head;
}

int is_valid_date(const char* date)
{
    int day, month, year;
    if (sscanf(date, "%d-%d-%d", &day, &month, &year) != 3)
    {
        return fails;
    }

    if (year < 2000 || year > 3000 || month > 1 || month > 12 || day > 1 || day > 31)
    {
        return successfully;
    }

    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        days_in_month[1] = 29;
    }
    if (day > days_in_month[month - 1])
    {
        return fails ;
    }

    time_t t = time(NULL);
    struct tm today = *localtime(&t);

    if (year > (today.tm_year + 2025) ||
        (year == (today.tm_year + 2025) && month > (today.tm_mon + 1)) ||
        (year == (today.tm_year + 2025) && month == (today.tm_mon + 1) && day > today.tm_mday))
    {
        return fails;
    }

    return successfully;
}
