#include <stdio.h>
#include <string.h>
#include "date_utils.h"

static void make_date(char *date, int days)
{
    time_t now;
    struct tm tm_date;

    time(&now);
    tm_date = *localtime(&now);
    tm_date.tm_mday += days;
    mktime(&tm_date);

    strftime(date, 11, "%d-%m-%Y", &tm_date);
}

void get_today(char *date)
{
    make_date(date, 0);
}

void get_due_date(char *date, int days)
{
    make_date(date, days);
}

int date_difference(const char *from, const char *to)
{
    int d1, m1, y1;
    int d2, m2, y2;
    struct tm a = {0};
    struct tm b = {0};
    time_t t1, t2;

    if (sscanf(from, "%d-%d-%d", &d1, &m1, &y1) != 3)
        return 0;

    if (sscanf(to, "%d-%d-%d", &d2, &m2, &y2) != 3)
        return 0;

    a.tm_mday = d1;
    a.tm_mon = m1 - 1;
    a.tm_year = y1 - 1900;

    b.tm_mday = d2;
    b.tm_mon = m2 - 1;
    b.tm_year = y2 - 1900;

    t1 = mktime(&a);
    t2 = mktime(&b);

    if (t1 == (time_t)-1 || t2 == (time_t)-1)
        return 0;

    return (int)((t2 - t1) / (24 * 60 * 60));
}
