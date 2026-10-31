#ifndef BOOK_H
#define BOOK_H

#define TITLE_SIZE 80
#define AUTHOR_SIZE 60

typedef struct
{
    int id;
    char title[TITLE_SIZE];
    char author[AUTHOR_SIZE];
    int quantity;
} Book;

void add_book(void);
void update_book(void);
void remove_book(void);
void search_book(void);
void view_all_books(void);
int find_book_by_id(int id);
int get_book_quantity(int id);
void change_book_quantity(int id, int change);
int get_book_title(int id, char *title);

#endif
