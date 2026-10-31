#include <stdio.h>
#include "book.h"
#include "issue.h"
#include "report.h"
#include "login.h"
#include "input.h"

static void show_menu(void)
{
    printf("\n========================================\n");
    printf("        LIBRARY MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Add New Book\n");
    printf("2. Update Book Details\n");
    printf("3. Remove Book\n");
    printf("4. Search Book\n");
    printf("5. View All Books\n");
    printf("6. Issue Book\n");
    printf("7. Return Book\n");
    printf("8. List Issued Books\n");
    printf("9. Save\n");
    printf("10. Reports\n");
    printf("11. Exit\n");
    printf("========================================\n");
}

int main(void)
{
    int choice;

    if (!login())
        return 0;

    while (1)
    {
        show_menu();
        choice = read_int("Enter your choice: ");

        switch (choice)
        {
            case 1:
                add_book();
                break;

            case 2:
                update_book();
                break;

            case 3:
                remove_book();
                break;

            case 4:
                search_book();
                break;

            case 5:
                view_all_books();
                break;

            case 6:
                issue_book();
                break;

            case 7:
                return_book();
                break;

            case 8:
                list_issued_books();
                break;

            case 9:
                printf("Data is already saved to the files after each operation.\n");
                break;

            case 10:
                show_reports();
                break;

            case 11:
                printf("Exiting Library Management System.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
