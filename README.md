
LIBRARY MANAGEMENT SYSTEM IN C
===============================

This project is based on the Book Management Module specification.

FILES
-----
main.c          Main menu and program flow
book.c/.h       Add, update, remove, search and display books
issue.c/.h      Issue, return and issued-book records
user.c/.h       User record handling
date_utils.c/.h Date generation and date difference
input.c/.h      Simple input validation functions
login.c/.h      Admin login
report.c/.h     Basic report
file_utils.h    Names of data files
Makefile        Builds the complete project

COMPILE
-------
make

RUN
---
./lms

CLEAN
-----
make clean

LOGIN
-----
Username: admin
Password: admin123

DATA FILES
----------
books.dat
users.dat
issues.dat

The files are created automatically when data is added.

MAIN FEATURES
-------------
1. Add New Book
2. Update Book Details
3. Remove Book
4. Search Book
5. View All Books
6. Issue Book
7. Return Book
8. List Issued Books
9. Save
10. Reports
11. Exit

ISSUE RULE
----------
A book is issued only when quantity is available.
Issue date is generated automatically.
Due date is 7 days from issue date.
Book quantity is reduced after issue.

RETURN RULE
-----------
Return date is generated automatically.
Late days are calculated from due date.
Fine = late days * Rs.5.
Book quantity is increased after return.

SEARCH
------
Book search supports ID, partial book name and partial author name.
Text search is case-insensitive.

NOTES
-----
This is a simple console project intended for learning C structures,
file handling, functions and multiple source files.
