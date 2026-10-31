#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include <time.h>

void get_today(char *date);
void get_due_date(char *date, int days);
int date_difference(const char *from, const char *to);

#endif
