#include <stdio.h>
#include <string.h>
#include "issue.h"
#include "book.h"
#include "user.h"
#include "date_utils.h"
#include "input.h"
#include "file_utils.h"

static int next_issue_id(void)
{
    FILE *fp;
    Issue issue;
    int id = 1;

    fp = fopen(ISSUE_FILE, "rb");
    if (fp == NULL)
        return id;

    while (fread(&issue, sizeof(Issue), 1, fp) == 1)
    {
        if (issue.issue_id >= id)
            id = issue.issue_id + 1;
    }

    fclose(fp);
    return id;
}

int has_active_issue(int book_id, int user_id)
{
    FILE *fp = fopen(ISSUE_FILE, "rb");
    Issue issue;

    if (fp == NULL)
        return 0;

    while (fread(&issue, sizeof(Issue), 1, fp) == 1)
    {
        /* Only an active issue blocks a new issue.
           A returned issue can be issued again. */
        if (issue.book_id == book_id &&
            issue.user_id == user_id &&
            issue.returned == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void issue_book(void)
{
    FILE *fp;
    Issue issue;
    User user;
    int book_id;
    int user_id;
    char name[NAME_SIZE];

    book_id = read_int("Enter book ID: ");

    if (!find_book_by_id(book_id))
    {
        printf("Book not found.\n");
        return;
    }

    if (get_book_quantity(book_id) <= 0)
    {
        printf("Book is not available right now.\n");
        return;
    }

    user_id = read_int("Enter user ID: ");

    if (user_id <= 0)
    {
        printf("User ID must be positive.\n");
        return;
    }

    if (has_active_issue(book_id, user_id))
    {
        printf("This user already has this book issued.\n");
        return;
    }

    if (find_user(user_id, &user))
    {
        strcpy(name, user.name);
        printf("User found: %s\n", name);
    }
    else
    {
        read_non_empty("Enter user name: ", name, NAME_SIZE);
        add_or_update_user(user_id, name);
    }

    issue.issue_id = next_issue_id();
    issue.book_id = book_id;
    issue.user_id = user_id;
    strcpy(issue.user_name, name);
    get_today(issue.issue_date);
    get_due_date(issue.due_date, 7);
    strcpy(issue.return_date, "-");
    issue.fine = 0;
    issue.returned = 0;

    fp = fopen(ISSUE_FILE, "ab");
    if (fp == NULL)
    {
        perror("Unable to open issue file");
        return;
    }

    fwrite(&issue, sizeof(Issue), 1, fp);
    fclose(fp);

    change_book_quantity(book_id, -1);

    printf("\nBook issued successfully.\n");
    printf("Issue date: %s\n", issue.issue_date);
    printf("Due date  : %s\n", issue.due_date);
}

void return_book(void)
{
    FILE *fp;
    Issue issue;
    int book_id;
    int user_id;
    int found = 0;
    int late_days;

    book_id = read_int("Enter book ID: ");
    user_id = read_int("Enter user ID: ");

    fp = fopen(ISSUE_FILE, "r+b");
    if (fp == NULL)
    {
        printf("No issue records found.\n");
        return;
    }

    while (fread(&issue, sizeof(Issue), 1, fp) == 1)
    {
        if (issue.book_id == book_id &&
            issue.user_id == user_id &&
            issue.returned == 0)
        {
            found = 1;

            get_today(issue.return_date);

            late_days = date_difference(issue.due_date, issue.return_date);

            if (late_days > 0)
                issue.fine = late_days * 5.0f;
            else
                issue.fine = 0;

            issue.returned = 1;

            fseek(fp, -(long)sizeof(Issue), SEEK_CUR);
            fwrite(&issue, sizeof(Issue), 1, fp);

            change_book_quantity(book_id, 1);

            printf("\nBook returned successfully.\n");
            printf("Return date: %s\n", issue.return_date);
            printf("Fine       : Rs. %.2f\n", issue.fine);
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Active issue record not found.\n");
}

void list_issued_books(void)
{
    FILE *fp;
    Issue issue;
    char title[80];
    int found = 0;

    fp = fopen(ISSUE_FILE, "rb");
    if (fp == NULL)
    {
        printf("No issue records found.\n");
        return;
    }

    printf("\n%-5s %-6s %-25s %-8s %-20s %-12s %-12s %-12s %-8s\n",
           "IID", "BID", "BOOK", "UID", "USER", "ISSUE", "DUE", "RETURN", "FINE");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    while (fread(&issue, sizeof(Issue), 1, fp) == 1)
    {
        get_book_title(issue.book_id, title);

        printf("%-5d %-6d %-25s %-8d %-20s %-12s %-12s %-12s %-8.2f\n",
               issue.issue_id,
               issue.book_id,
               title,
               issue.user_id,
               issue.user_name,
               issue.issue_date,
               issue.due_date,
               issue.return_date,
               issue.fine);

        found = 1;
    }

    fclose(fp);

    if (!found)
        printf("No issue records found.\n");
}
