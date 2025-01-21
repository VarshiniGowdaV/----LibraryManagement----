#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
enum returnvalue
{
    fails=0,
    successfully
};
struct student* student_head = NULL;

struct student* add_student(struct student* head, const char* name, int student_id, const char* department)
{
    if(student_id <= 0)
    {
        printf("Student ID must be a positive integer.\n");
        return student_head;
    }
    struct student* temp = student_head;
    while(temp != NULL)
    {
        if(temp->student_id == student_id)
        {
            printf("Student ID %d already exits.\n",student_id);
            return student_id;
        }
        temp = temp->next;
    }
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (new_student == NULL)
    {
        printf("Memory allocation failed\n");
        return head;
    }

    new_student->student_id = student_id;
    strncpy(new_student->name, name, MAX_NAME_LENGTH - 1);
    new_student->name[MAX_NAME_LENGTH - 1] = '\0';
    strncpy(new_student->department, department, MAX_DEPT_LENGTH - 1);
    new_student->department[MAX_DEPT_LENGTH - 1] = '\0';
    new_student->next = head;

    return new_student;
}
void update_student(struct student* head, int student_id, const char* new_name, const char* new_department)
{
    struct student* current = head;

    while (current != NULL)
    {
        if (current->student_id == student_id)
        {
            strncpy(current->name, new_name, MAX_NAME_LENGTH - 1);
            current->name[MAX_NAME_LENGTH - 1] = '\0';
            strncpy(current->department, new_department, MAX_DEPT_LENGTH - 1);
            current->department[MAX_DEPT_LENGTH - 1] = '\0';
            return successfully;
        }
        current = current->next;
    }

    printf("Student with ID %d  found\n", student_id);
    return fails;
}

void view_students(struct student* head)
{
    struct student* current = head;

    while (current != NULL)
    {
        printf("Student ID: %d\n", current->student_id);
        printf("Name: %s\n", current->name);
        printf("Department: %s\n", current->department);
        printf("-----------------------\n");
        current = current->next;
    }
}

void delete_student(struct student* head, int student_id)
{
    struct student* current = head;
    struct student* previous = NULL;
    if (current != NULL && current->student_id == student_id)
    {
        head = current->next;
        free(current);
        return successfully;
    }
    while (current != NULL && current->student_id != student_id)
    {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        printf("Student with ID %d not found\n", student_id);
        return fails;
    }
    previous->next = current->next;
    free(current);
}
struct student* search_student(struct student* head, int student_id)
{
    struct student* current = head;

    while (current != NULL)
    {
        if (current->student_id == student_id)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}
void sortStudentsByID()
{
    if (student_head == NULL)
        return successfully;

    struct student* i = student_head;
    struct student* j = NULL;
    struct student temp;
    while (i != NULL)
    {
        j = i->next;
        while (j != NULL)
        {
            if (i->student_id > j->student_id)
            {
                temp = *i;
                *i = *j;
                *j = temp;
            }
            j = j->next;
        }
        i = i->next;
    }
}
void sortStudentsByName()
{
    if (student_head == NULL)
        return successfully;

    struct student* i = student_head;
    struct student* j = NULL;
    struct student temp;
    while (i != NULL)
    {
        j = i->next;
        while (j != NULL)
        {
            if (strcmp(i->name, j->name) > 0)
            {
                temp = *i;
                *i = *j;
                *j = temp;
            }
            j = j->next;
        }
        i = i->next;
    }
}
void searchStudentById(int id)
{
    struct student* student = search_student(student_head, id);
    if (student != NULL)
    {
        printf("Student ID: %d\n", student->student_id);
        printf("Name: %s\n", student->name);
        printf("Department: %s\n", student->department);
    }
    else
    {
        printf("Student with ID %d not found\n", id);
    }
}
int getTotalStudentCount()
{
    int count = 0;
    struct student* current = student_head;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}
int is_student_id_exits(struct student* head,int student_id)
{
    struct student* current = head;
    while (current != NULL)
    {
        if(current->student_id == student_id)
        {
            return successfully;
        }
        current = current->next;
    }
    return fails;
}
