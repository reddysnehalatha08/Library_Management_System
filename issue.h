#ifndef ISSUE_H
#define ISSUE_H

#define NAME_SIZE 60

typedef struct
{
    int issue_id;
    int book_id;
    int user_id;
    char user_name[NAME_SIZE];
    char issue_date[11];
    char due_date[11];
    char return_date[11];
    float fine;
    int returned;
} Issue;

void issue_book(void);
void return_book(void);
void list_issued_books(void);
int has_active_issue(int book_id, int user_id);

#endif
