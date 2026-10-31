#include <stdio.h>
#include <string.h>
#include "input.h"

int login(void)
{
    char username[30];
    char password[30];

    printf("\n========== Admin Login ==========\n");
    read_non_empty("Username: ", username, sizeof(username));
    read_non_empty("Password: ", password, sizeof(password));

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
    {
        printf("Login successful.\n");
        return 1;
    }

    printf("Invalid username or password.\n");
    return 0;
}
