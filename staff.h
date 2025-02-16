
#ifndef STAFF_H
#define STAFF_H


#define MAX_POSITION_LENGTH 50
#define MAX_DEPARTMENT_LENGTH 100
#define MAX_NAME_LENGTH 100
#define MAX_DEPT_LENGTH 50
struct staff {
    int staff_id;
    char name[MAX_NAME_LENGTH];
    char department[MAX_DEPARTMENT_LENGTH];

    char position[50];
    struct staff* next;
};
extern struct staff* staff_head;
extern int staff_id;
struct staff* add_staff(struct staff* staff_head, const char* name, int staff_id, const char* department);
void delete_staff(struct staff* head, int id);
void update_staff(struct staff* head, int staff_id, const char* staff_name, const char* staff_department);
struct staff* search_staff(struct staff* head, int id);
void view_staff(struct staff* head);
void sortStaffsByName();
void sortStaffsById(struct staff* head);
int getTotalStaffCount();
#endif // STAFF_H
