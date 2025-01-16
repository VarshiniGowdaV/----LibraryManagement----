#ifndef RETURNEDBOOK_H
#define RETURNEDBOOK_H

#define MAX_DATE_LENGTH 11

struct returnedbook {
    int returned_id;
    int student_id;
    int book_id;
    char returned_date[MAX_DATE_LENGTH];
    struct returnedbook* next;
};
extern struct returnedbook* returned_books_head;

struct returnedbook* add_returned_book(struct returnedbook* head, int student_id, int book_id, const char* date);
void record_returned_book();
void view_returned_books();
void print_returned_books();

#endif  // RETURNEDBOOK_H
