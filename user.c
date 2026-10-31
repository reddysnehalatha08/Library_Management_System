#include <stdio.h>
#include <string.h>
#include "user.h"
#include "file_utils.h"

int find_user(int id, User *user)
{
    FILE *fp;
    User temp;

    fp = fopen(USER_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&temp, sizeof(User), 1, fp) == 1)
    {
        if (temp.id == id)
        {
            if (user != NULL)
                *user = temp;

            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void add_or_update_user(int id, const char *name)
{
    FILE *fp;
    User user;

    fp = fopen(USER_FILE, "ab");
    if (fp == NULL)
        return;

    user.id = id;
    snprintf(user.name, sizeof(user.name), "%s", name);

    fwrite(&user, sizeof(User), 1, fp);
    fclose(fp);
}
