#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"
enum returnvalue
{
    fails=0,
    successfully
};
struct staff* staff_head = NULL;

struct staff* add_staff(struct staff* staff_head, const char* name, int staff_id, const char* department)
{
    if(staff_id <= 0)
    {
        printf("Staff ID must be positive integer.\n");
        return staff_head;
    }
    struct staff* temp = staff_head;
    while(temp != NULL)
    {
        if(temp->staff_id == staff_id)
        {
            printf("Staff ID %d already exits.\n",staff_id);
            return staff_head;
        }
        temp = temp->next;
    }
    struct staff* new_staff = (struct staff*)malloc(sizeof(struct staff));
    if (!new_staff)
    {
        printf("Memory allocation failed!\n");
        return staff_head;
    }
    strncpy(new_staff->name, name, MAX_NAME_LENGTH - 1);
    new_staff->name[MAX_NAME_LENGTH - 1] = '\0';
    new_staff->staff_id = staff_id;
    strncpy(new_staff->department, department, MAX_DEPARTMENT_LENGTH - 1);
    new_staff->department[MAX_DEPARTMENT_LENGTH - 1] = '\0';
    new_staff->next = NULL;
    if (staff_head == NULL)
    {
        staff_head = new_staff;
    } else {
        struct staff* current = staff_head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_staff;
    }

    return staff_head;
}

void delete_staff(struct staff* head, int id)
{
    struct staff *current = head, *previous = NULL;
    while (current != NULL)
    {
        if (current->staff_id == id)
        {
            if (previous == NULL)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            printf("Staff with ID %d deleted.\n", id);
            return successfully;
        }
        previous = current;
        current = current->next;
    }
    printf("Staff with ID %d not found.\n", id);
}

void update_staff(struct staff* head, int staff_id, const char* staff_name, const char* staff_department)
{
    struct staff* current = head;
    while (current != NULL)
    {
        if (current->staff_id == staff_id)
        {
            strncpy(current->name, staff_name, MAX_NAME_LENGTH);
            strncpy(current->department, staff_department, MAX_DEPT_LENGTH);
            printf("Staff updated: ID: %d, Name: %s, Department: %s\n",
                   current->staff_id, current->name, current->department);
            return successfully;
        }
        current = current->next;
    }
    printf("Staff with ID %d not found.\n", staff_id);
}
struct staff* search_staff(struct staff* head, int id)
{
    struct staff* current = head;
    while (current != NULL)
    {
        if (current->staff_id == id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void view_staff(struct staff* head)
{
    struct staff* current = head;
    if (current == NULL)
    {
        printf("staff records available.\n");
        return successfully;
    }

    printf("Staff details:\n");
    while (current != NULL)
    {
        printf("ID: %d, Name: %s, Department: %s, Position: %s\n",
               current->staff_id, current->name, current->department, current->position);
        current = current->next;
    }
}
// void sortStaffByName(struct staff* head)
// {
//     struct staff *current, *next_node;
//     char temp_name[MAX_NAME_LENGTH], temp_department[MAX_DEPARTMENT_LENGTH], temp_position[50];
//     int temp_id;

//     for (current = head; current != NULL; current = current->next)
//     {
//         for (next_node = current->next; next_node != NULL; next_node = next_node->next)
//         {
//             if (strcmp(current->name, next_node->name) > 0)
//             {
//                 temp_id = current->staff_id;
//                 current->staff_id = next_node->staff_id;
//                 next_node->staff_id = temp_id;

//                 strncpy(temp_name, current->name, sizeof(temp_name));
//                 strncpy(current->name, next_node->name, sizeof(current->name));
//                 strncpy(next_node->name, temp_name, sizeof(next_node->name));

//                 strncpy(temp_department, current->department, sizeof(temp_department));
//                 strncpy(current->department, next_node->department, sizeof(current->department));
//                 strncpy(next_node->department, temp_department, sizeof(next_node->department));

//                 strncpy(temp_position, current->position, sizeof(temp_position));
//                 strncpy(current->position, next_node->position, sizeof(current->position));
//                 strncpy(next_node->position, temp_position, sizeof(next_node->position));
//             }
//         }
//     }
// }
// void sortStaffById(struct staff* head)
// {
//     struct staff *current, *next_node;
//     int temp_id;
//     char temp_name[MAX_NAME_LENGTH], temp_department[MAX_DEPARTMENT_LENGTH], temp_position[50];

//     for (current = head; current != NULL; current = current->next)
//     {
//         for (next_node = current->next; next_node != NULL; next_node = next_node->next)
//         {
//             if (current->staff_id > next_node->staff_id)
//             {
//                 temp_id = current->staff_id;
//                 current->staff_id = next_node->staff_id;
//                 next_node->staff_id = temp_id;
//                 strncpy(temp_name, current->name, sizeof(temp_name));
//                 strncpy(current->name, next_node->name, sizeof(current->name));
//                 strncpy(next_node->name, temp_name, sizeof(next_node->name));

//                 strncpy(temp_department, current->department, sizeof(temp_department));
//                 strncpy(current->department, next_node->department, sizeof(current->department));
//                 strncpy(next_node->department, temp_department, sizeof(next_node->department));

//                 strncpy(temp_position, current->position, sizeof(temp_position));
//                 strncpy(current->position, next_node->position, sizeof(current->position));
//                 strncpy(next_node->position, temp_position, sizeof(next_node->position));
//             }
//         }
//     }
// }
void sortStaffsByID()
{
    if (staff_head == NULL)
        return successfully;

    struct staff* i = staff_head;
    struct staff* j = NULL;
    struct staff temp;
    while (i != NULL)
    {
        j = i->next;
        while (j != NULL)
        {
            if (i->staff_id > j->staff_id)
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
void sortStaffsByName()
{
    if (staff_head == NULL)
        return successfully;

    struct staff* i = staff_head;
    struct staff* j = NULL;
    struct staff temp;
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

int getTotalStaffCount(struct staff* head)
{
    int count = 0;
    struct staff* current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}
int is_staff_id_exists(struct staff* head, int staff_id)
{
    struct staff* current = head;
    while (current != NULL)
    {
        if (current->staff_id == staff_id)
        {
            return successfully;
        }
        current = current->next;
    }
    return fails;
}
