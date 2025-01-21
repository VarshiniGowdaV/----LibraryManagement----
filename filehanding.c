#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filehanding.h"
#include "student.h"
#include "staff.h"
#include "book.h"
#include "borrowedbook.h"
#include "filehanding.h"
#include "retunedbook.h"

#define Books_FILE "books.txt"
#define student_FILE "student.txt"
#define Staff_FILE "staff.txt"
#define Returned_book_FILE "returned_books.txt"
#define BORROWED_BOOKS_FILE "borrowed_books.txt"
struct borrowed_book_node *borrowed_books_head = NULL;

static FILE* openFile(const char* filename)
{
    FILE* file = fopen(filename, "r+");
    if (!file)
    {
        file = fopen(filename, "w+");
        if (!file)
        {
            printf("Error opening file: %s\n", filename);
            exit(1);
        }
    }
    return file;
}

void loadStudentsFromFile()
{
    FILE* file = openFile("students.txt");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (file_size > 0)
    {
        struct student temp_student;
        while (fread(&temp_student, sizeof(struct student), 1, file))
        {
            student_head = add_student(student_head, temp_student.name, temp_student.student_id, temp_student.department);
        }
    }
    fclose(file);
}
void addStudentToFile()
{
    FILE* file = openFile("students.txt");

    struct student* new_student = student_head;
    fseek(file, 0, SEEK_END);
    while (new_student != NULL)
    {
        fprintf(file,"%5d %-99s %-49s\n",new_student->student_id ,new_student->name,new_student->department);
        new_student = new_student->next;
    }
    fclose(file);
}
void deleteStudentInFile(int studentId)
{
    FILE *file = fopen("students.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening file for deletion.\n");
        return ;
    }

    char line[512];
    long position;
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        int existingStudentId;
        sscanf(line, "%d", &existingStudentId);

        if (existingStudentId == studentId)
        {
            found = 1;
            position = ftell(file) - strlen(line);
            fseek(file, position + 153, SEEK_SET);
            fprintf(file, "D");
            fflush(file);
            break;
        }
    }

    if (found == 0)
    {
        printf("Student with ID %d not found.\n", studentId);
    }

    fclose(file);
}

long findStudentPosition(int student_id)
{
    FILE* file = openFile("students.txt");
    fseek(file, 0, SEEK_SET);
    struct student temp_student;
    long position = 0;

    while (fread(&temp_student, sizeof(struct student), 1, file))
    {
        if (temp_student.student_id == student_id)
        {
            fclose(file);
            return position;
        }
        position++;
    }
    fclose(file);
    return -1;
}
void updateStudentInFile(int studentId, int fieldToUpdate, void *newValue)
{
    FILE *file = fopen("students.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening students.txt for updating.\n");
        return;
    }

    rewind(file);
    char line[512];
    long position = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        int existingStudentId;
        sscanf(line, "%d", &existingStudentId);

        if (existingStudentId == studentId)
        {
            found = 1;
            position = ftell(file) - strlen(line);
            fseek(file, position, SEEK_SET);

            switch (fieldToUpdate)
            {
            case 1:
                fseek(file, position + 5, SEEK_SET);
                fprintf(file, "%-99s", (char *)newValue);
                break;
            case 2:
                fseek(file, position + 104, SEEK_SET);
                fprintf(file, "%-49s", (char *)newValue);
                break;
            default:
                printf("Invalid field selected for update.\n");
                break;
            }
            fflush(file);
            break;
        }
    }

    if (found == 0)
    {
        printf("Student with ID %d not found.\n", studentId);
    }

    fclose(file);
}

void save_student_to_file()
{
    FILE* file = openFile("students.txt");

    struct student* current = student_head;
    fseek(file, 0, SEEK_SET);
    while (current != NULL)
    {
        fwrite(current, sizeof(struct student), 1, file);
        current = current->next;
    }

    fclose(file);
}
//***********************************************************************************************************************//

void loadBooksFromFile()
{
    FILE* file = openFile("books.txt");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > 0)
    {
        struct book temp_book;
        while (fread(&temp_book, sizeof(struct book), 1, file))
        {
            book_head = add_book(book_head, temp_book.name, temp_book.title, temp_book.book_id, temp_book.author);
        }
    }
    fclose(file);
}
void addBooksToFile()
{
    FILE* file = openFile("books.txt");

    struct book* current = book_head;
    fseek(file, 0, SEEK_END);
    while (current != NULL)
    {
        fprintf(file, "%5d %-99s %-49s\n", current->book_id, current->title, current->author);
        current = current->next;
    }
    fclose(file);
}

void deleteBookInFile(int bookId)
{
    FILE *file = fopen("books.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening file for deletion.\n");
        return;
    }

    char line[512];
    long position;
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        int existingBookId;
        sscanf(line, "%d", &existingBookId);

        if (existingBookId == bookId)
        {
            found = 1;
            position = ftell(file) - strlen(line);
            fseek(file, position + 153, SEEK_SET);
            fprintf(file, "D");
            fflush(file);
            break;
        }
    }

    if (found == 0)
    {
        printf("Book with ID %d not found.\n", bookId);
    }

    fclose(file);
}

long findBooksPosition(int book_id)
{
    FILE* file = openFile("books.txt");
    fseek(file, 0, SEEK_SET);
    struct book temp_book;
    long position = 0;

    while (fread(&temp_book, sizeof(struct book), 1, file))
    {
        if (temp_book.book_id == book_id)
        {
            fclose(file);
            return position;
        }
        position++;
    }
    fclose(file);
    return -1;
}
void updateBookInFile(int bookId, int fieldToUpdate, void *newValue)
{
    FILE *file = fopen("books.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening books.txt for updating.\n");
        return;
    }

    rewind(file);
    char line[512];
    long position = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        int existingBookId;
        sscanf(line, "%d", &existingBookId);

        if (existingBookId == bookId)
        {
            found = 1;
            position = ftell(file) - strlen(line);
            fseek(file, position, SEEK_SET);

            switch (fieldToUpdate)
            {
            case 1:
                fseek(file, position + 5, SEEK_SET);
                fprintf(file, "%-99s", (char *)newValue);
                break;
            case 2:
                fseek(file, position + 104, SEEK_SET);
                fprintf(file, "%-49s", (char *)newValue);
                break;
            default:
                printf("Invalid field selected for update.\n");
                break;
            }
            fflush(file);
            break;
        }
    }

    if (found == 0)
    {
        printf("Book with ID %d not found.\n", bookId);
    }

    fclose(file);
}


void save_Book_To_File()
{
    FILE* file = openFile("books.txt");

    struct book* current = book_head;
    fseek(file, 0, SEEK_SET);
    while (current != NULL)
    {
        fwrite(current, sizeof(struct book), 1, file);
        current = current->next;
    }

    fclose(file);
}

//*****************************************************************************************************************//

void loadStaffFromFile()
{
    FILE* file = openFile("staff.txt");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > 0)
    {
        struct staff temp_staff;
        while (fread(&temp_staff, sizeof(struct staff), 1, file))
        {
            staff_head = add_staff(staff_head, temp_staff.name, temp_staff.staff_id, temp_staff.department);
        }
    }
    fclose(file);
}

void addStaffToFile()
{
    FILE* file = openFile("staff.txt");

    struct staff* new_staff = staff_head;
    fseek(file, 0, SEEK_END);
    while (new_staff != NULL)
    {
        fprintf(file, "%5d %-99s %-49s\n", new_staff->staff_id, new_staff->name, new_staff->department);
        new_staff = new_staff->next;
    }
    fclose(file);
}

long findStaffPosition(int staff_id)
{
    FILE* file = openFile("staff.txt");
    fseek(file, 0, SEEK_SET);
    struct staff temp_staff;
    long position = 0;

    while (fread(&temp_staff, sizeof(struct staff), 1, file))
    {
        if (temp_staff.staff_id == staff_id)
        {
            fclose(file);
            return position;
        }
        position++;
    }
    fclose(file);
    return -1;
}

void deleteStaffInFile(int staffId)
{
    FILE *file = fopen("staff.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening file for deletion.\n");
        return;
    }

    char line[512];
    long position;
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        int existingStaffId;
        sscanf(line, "%d", &existingStaffId);

        if (existingStaffId == staffId)
        {
            found = 1;
            position = ftell(file) - strlen(line);
            fseek(file, position + 153, SEEK_SET);
            fprintf(file, "D");
            fflush(file);
            break;
        }
    }

    if (found == 0)
    {
        printf("Staff with ID %d not found.\n", staffId);
    }

    fclose(file);
}


void updateStaffInFile(int staffId, int fieldToUpdate, void *newValue)
{
    FILE *file = fopen("staff.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening staff.txt for updating.\n");
        return;
    }

    rewind(file);
    char line[512];
    long position = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        int existingStaffId;
        sscanf(line, "%d", &existingStaffId);

        if (existingStaffId == staffId)
        {
            found = 1;
            position = ftell(file) - strlen(line);
            fseek(file, position, SEEK_SET);

            switch (fieldToUpdate)
            {
            case 1:
                fseek(file, position + 5, SEEK_SET);
                fprintf(file, "%-99s", (char *)newValue);
                break;
            case 2:
                fseek(file, position + 104, SEEK_SET);
                fprintf(file, "%-49s", (char *)newValue);
                break;
            case 3:
                fseek(file, position + 154, SEEK_SET);
                fprintf(file, "%-30s", (char *)newValue);
                break;
            default:
                printf("Invalid field selected for update.\n");
                break;
            }
            fflush(file);
            break;
        }
    }

    if (found == 0)
    {
        printf("Staff with ID %d not found.\n", staffId);
    }

    fclose(file);
}

void saveStaffToFile()
{
    FILE* file = openFile("staff.txt");

    struct staff* current = staff_head;
    fseek(file, 0, SEEK_SET);

    while (current != NULL)
    {
        fwrite(current, sizeof(struct staff), 1, file);
        current = current->next;
    }

    fclose(file);
}
//****************************************************************************************************************//
void loadBorrowedBookFromFile(void)
{
    FILE* file = openFile(BORROWED_BOOKS_FILE);
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > 0)
    {
        struct borrowedbook temp_borrowed_book;
        while (fread(&temp_borrowed_book, sizeof(struct borrowedbook), 1, file))
        {
            borrowedbook_head = add_borrowed_book(borrowedbook_head, temp_borrowed_book.student_id, temp_borrowed_book.book_id, temp_borrowed_book.borrowed_date);
        }
    }

    fclose(file);
    printf("Borrowed books loaded successfully.\n");
}

void save_Borrowed_Book_To_File()
{
    FILE* file = openFile(BORROWED_BOOKS_FILE);
    struct borrowedbook* current = borrowedbook_head;

    fseek(file, 0, SEEK_SET);

    while (current != NULL)
    {
        fwrite(current, sizeof(struct borrowedbook), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Borrowed books saved to file successfully.\n");
}
//*******************************************************************************************************************//

void save_Retuned_Book_To_File()
{
    FILE* file = fopen("returned_books.txt", "w");
    if (file == NULL)
    {
        printf("Error: Could not open file for saving returned books.\n");
        return;
    }

    struct returnedbook* temp = returned_books_head;
    while (temp != NULL)
    {
        fprintf(file, "%d %d %d %s\n", temp->returned_id, temp->student_id, temp->book_id, temp->returned_date);
        temp = temp->next;
    }

    fclose(file);
    printf("Returned books have been saved to the file.\n");
}

void loadRetunedBookFromFile()
{
    FILE* file = fopen("returned_books.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open file for loading returned books.\n");
        return;
    }
    struct returnedbook* temp;
    while (returned_books_head != NULL) {
        temp = returned_books_head;
        returned_books_head = returned_books_head->next;
        free(temp);
    }

    int returned_id, student_id, book_id;
    char returned_date[MAX_DATE_LENGTH];

    while (fscanf(file, "%d %d %d %s", &returned_id, &student_id, &book_id, returned_date) == 4)
    {
        struct returnedbook* new_book = (struct returnedbook*)malloc(sizeof(struct returnedbook));
        if (new_book == NULL)
        {
            printf("Memory allocation failed while loading returned books.\n");
            fclose(file);
            return;
        }

        new_book->returned_id = returned_id;
        new_book->student_id = student_id;
        new_book->book_id = book_id;
        strncpy(new_book->returned_date, returned_date, MAX_DATE_LENGTH);
        new_book->next = returned_books_head;
        returned_books_head = new_book;
    }

    fclose(file);
    printf("Returned books have been loaded from the file.\n");
}
