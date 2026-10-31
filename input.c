#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

void read_line(char *str, int size)
{
    if (fgets(str, size, stdin) == NULL)
    {
        str[0] = '\0';
        return;
    }

    str[strcspn(str, "\n")] = '\0';
}

int read_int(const char *message)
{
    char line[100];
    char *end;
    long value;

    while (1)
    {
        printf("%s", message);
        read_line(line, sizeof(line));

        value = strtol(line, &end, 10);

        if (end != line && *end == '\0')
            return (int)value;

        printf("Please enter a valid number.\n");
    }
}

float read_float(const char *message)
{
    char line[100];
    char *end;
    float value;

    while (1)
    {
        printf("%s", message);
        read_line(line, sizeof(line));

        value = strtof(line, &end);

        if (end != line && *end == '\0')
            return value;

        printf("Please enter a valid number.\n");
    }
}

void read_non_empty(const char *message, char *str, int size)
{
    do
    {
        printf("%s", message);
        read_line(str, size);

        if (str[0] == '\0')
            printf("This field cannot be empty.\n");

    } while (str[0] == '\0');
}
