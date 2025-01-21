#include <stdio.h>
#include <string.h>
#include "admin.h"
enum returnvalue
{
    fails=0,
    successfully
};

int authenticate_user(const char *correct_username, const char *correct_password, const char *role) {
    char entered_username[50];
    char entered_password[50];

    printf("Enter username for %s: ", role);
    fgets(entered_username, sizeof(entered_username), stdin);
    entered_username[strcspn(entered_username, "\n")] = '\0';
    // int a=strcspn(entered_username, "\n");
    // printf("%dwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",a);

    printf("Enter password for %s: ", role);
    fgets(entered_password, sizeof(entered_password), stdin);
    entered_password[strcspn(entered_password, "\n")] = '\0';

    if (strcmp(entered_username, correct_username) == 0 && strcmp(entered_password, correct_password) == 0) {
        return successfully;
    } else {
        return fails;
    }
}

int authenticate_admin() {
    const char *admin_username = "admin";
    const char *admin_password = "admin123";

    return authenticate_user(admin_username, admin_password, "admin");
}
