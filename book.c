#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "book.h"
#include "input.h"
#include "file_utils.h"

static int contains_text(const char *text, const char *key)
{
    char a[TITLE_SIZE];
    char b[TITLE_SIZE];
    int i;

    snprintf(a, sizeof(a), "%s", text);
    snprintf(b, sizeof(b), "%s", key);

    for (i = 0; a[i]; i++)
        a[i] = (char)tolower((unsigned char)a[i]);

    for (i = 0; b[i]; i++)
        b[i] = (char)tolower((unsigned char)b[i]);

    return strstr(a, b) != NULL;
}

int find_book_by_id(int id)
{
    FILE *fp;
    Book book;

    fp = fopen(BOOK_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&book, sizeof(Book), 1, fp) == 1)
    {
        if (book.id == id)
        {
            fclose(fp);
            return 1;  }
    }

    fclose(fp);
    return 0;
}

int get_book_quantity(int id)
{
    FILE *fp;
    Book book;

    fp = fopen(BOOK_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&book, sizeof(Book), 1, fp) == 1)
    {
        if (book.id == id)
        {
            fclose(fp);
            return book.quantity;
        }
    }

    fclose(fp);
    return 0;
}

int get_book_title(int id, char *title)
{
    FILE *fp;
    Book book;

    fp = fopen(BOOK_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&book, sizeof(Book), 1, fp) == 1) {
        if (book.id == id)
        {
            strcpy(title, book.title);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void change_book_quantity(int id, int change)
{
    FILE *fp;
    Book book;

    fp = fopen(BOOK_FILE, "r+b");
    if (fp == NULL)
        return;

    while (fread(&book, sizeof(Book), 1, fp) == 1)
    {
        if (book.id == id)
        {
            book.quantity += change;
            fseek(fp, -(long)sizeof(Book), SEEK_CUR);
            fwrite(&book, sizeof(Book), 1, fp);
            break;
        }
    }

    fclose(fp);
}

void add_book(void)
{
    FILE *fp;  Book book;

    book.id = read_int("Enter book ID: ");

    if (book.id <= 0)
    {
        printf("Book ID must be positive.\n");
        return;
    }

    if (find_book_by_id(book.id))
    {
        printf("Book ID already exists.\n");
        return;
    }

    read_non_empty("Enter book title: ", book.title, TITLE_SIZE);
    read_non_empty("Enter author name: ", book.author, AUTHOR_SIZE);

    do
    {
        book.quantity = read_int("Enter quantity: ");
        if (book.quantity < 0)
            printf("Quantity cannot be negative.\n");
    } while (book.quantity < 0);

    fp = fopen(BOOK_FILE, "ab");
    if (fp == NULL)
    {
        perror("Unable to open books file");
        return;
    }

    fwrite(&book, sizeof(Book), 1, fp);
    fclose(fp);

    printf("Book added successfully.\n");
}
void update_book(void)
{
    FILE *fp;
    Book book;
    int choice;
    int found = 0;
    char value[AUTHOR_SIZE > TITLE_SIZE ? AUTHOR_SIZE : TITLE_SIZE];

    printf("\n1. By Book ID\n");
    printf("2. By Book Name\n");
    printf("3. By Author Name\n");
    printf("4. Back\n");

    choice = read_int("Enter choice: ");

    if (choice == 4)
        return;

    if (choice < 1 || choice > 3)
    {
        printf("Invalid choice.\n");
        return;
    }

    fp = fopen(BOOK_FILE, "r+b");
    if (fp == NULL)
    {
        printf("No books available.\n");
        return;
    }

    if (choice == 1)
    {
        int id = read_int("Enter book ID: ");

        while (fread(&book, sizeof(Book), 1, fp) == 1)
        {
            if (book.id == id)
            {
                found = 1;
                break;
            }
        }
    }
    else
    {
        read_non_empty(choice == 2 ? "Enter book name: " : "Enter author name: ",
                       value, sizeof(value));

        while (fread(&book, sizeof(Book), 1, fp) == 1)
        {
            if ((choice == 2 && contains_text(book.title, value)) ||
                (choice == 3 && contains_text(book.author, value)))
            {
                found = 1;
                break;
            }
        }
    }

    if (!found)
    {
        fclose(fp);
        printf("Book not found.\n");
        return;
    }

    printf("Current title : %s\n", book.title);
    printf("Current author: %s\n", book.author);
    printf("Current qty   : %d\n", book.quantity);

    read_non_empty("Enter new title: ", book.title, TITLE_SIZE);
    read_non_empty("Enter new author: ", book.author, AUTHOR_SIZE);

    do
    {
        book.quantity = read_int("Enter new quantity: ");
        if (book.quantity < 0)
            printf("Quantity cannot be negative.\n");
    } while (book.quantity < 0);

    fseek(fp, -(long)sizeof(Book), SEEK_CUR);
    fwrite(&book, sizeof(Book), 1, fp);
    fclose(fp);

    printf("Book details updated.\n");
}

void remove_book(void)
{
FILE *fp, *temp;
Book book;
int choice;
int found = 0;
char value[TITLE_SIZE];


printf("\n1. By Book ID\n");
printf("2. By Book Name\n");
printf("3. By Author Name\n");
printf("4. Back\n");

choice = read_int("Enter choice: ");

if (choice == 4)
    return;

if (choice == 1)
{
    int id = read_int("Enter book ID: ");

    fp = fopen(BOOK_FILE, "rb");
    temp = fopen("books.tmp", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("Unable to open books file.\n");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    while (fread(&book, sizeof(Book), 1, fp) == 1)
    {
        if (book.id == id)
        {
            found = 1;
            continue;  }
        fwrite(&book, sizeof(Book), 1, temp);
    }
}
else if (choice == 2 || choice == 3)
{
    if (choice == 2)
        read_non_empty("Enter book name: ", value, TITLE_SIZE);
    else
        read_non_empty("Enter author name: ", value, TITLE_SIZE);

    fp = fopen(BOOK_FILE, "rb");
    temp = fopen("books.tmp", "wb");

    if (fp == NULL || temp == NULL)
    {
        printf("Unable to open books file.\n");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    while (fread(&book, sizeof(Book), 1, fp) == 1)
    {
        if ((choice == 2 && contains_text(book.title, value)) ||
            (choice == 3 && contains_text(book.author, value)))
        {
            found = 1;
            continue;
        }
        fwrite(&book, sizeof(Book), 1, temp);
    }
}
else
{
    printf("Invalid choice.\n");
    return;
} fclose(fp);
fclose(temp);

remove(BOOK_FILE);
rename("books.tmp", BOOK_FILE);

if (found)
    printf("Book removed successfully.\n");
else
    printf("Book not found.\n");


}




void search_book(void)
{
    FILE *fp;
    Book book;
    int choice;
    int found = 0;
    char value[TITLE_SIZE];

    printf("\n1. By Book ID\n");
    printf("2. By Book Name\n");
    printf("3. By Author Name\n");
    printf("4. Back\n");

    choice = read_int("Enter choice: ");

    if (choice == 4)
        return;

    fp = fopen(BOOK_FILE, "rb");
    if (fp == NULL)
    {
        printf("No books available.\n"); return;
    }

    if (choice == 1)
    {
        int id = read_int("Enter book ID: ");

        while (fread(&book, sizeof(Book), 1, fp) == 1)
        {
            if (book.id == id)
            {
                printf("\nID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\n",
                       book.id, book.title, book.author, book.quantity);
                found = 1;
                break;
            }
        }
    }
    else if (choice == 2 || choice == 3)
    {
        read_non_empty(choice == 2 ? "Enter book name: " : "Enter author name: ",
                        value, TITLE_SIZE);

        while (fread(&book, sizeof(Book), 1, fp) == 1)
        {
            if ((choice == 2 && contains_text(book.title, value)) ||
                (choice == 3 && contains_text(book.author, value)))
            {
                printf("\nID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\n",
                       book.id, book.title, book.author, book.quantity);
                found = 1;
            }
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }  fclose(fp);

    if (!found)
        printf("Book not found.\n");
}

void view_all_books(void)
{
    FILE *fp;
    Book book;

    fp = fopen(BOOK_FILE, "rb");
    if (fp == NULL)
    {
        printf("No books available.\n");
        return;
    }

    printf("\n%-6s %-30s %-25s %-8s\n", "ID", "TITLE", "AUTHOR", "QTY");
    printf("-----------------------------------------------------------------------\n");

    while (fread(&book, sizeof(Book), 1, fp) == 1)
    {
        printf("%-6d %-30s %-25s %-8d\n",
               book.id, book.title, book.author, book.quantity);
    }

    fclose(fp);
}
