#ifndef USER_H
#define USER_H

#define USER_NAME_SIZE 60

typedef struct
{
    int id;
    char name[USER_NAME_SIZE];
} User;

void add_or_update_user(int id, const char *name);
int find_user(int id, User *user);

#endif
