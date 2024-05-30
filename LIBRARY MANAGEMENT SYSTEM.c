#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

// Define the structure for book information
struct Book {
    char title[50];
    char author[50];
    int year;
};

// Function prototypes
void addBook(struct Book library[], int *bookCount);
void displayBooks(const struct Book library[], int bookCount);
void searchBook(const struct Book library[], int bookCount);
void removeBook(struct Book library[], int *bookCount);
void saveLibraryToFile(const struct Book library[], int bookCount);
void loadLibraryFromFile(struct Book library[], int *bookCount);

int main() {
    struct Book library[MAX_BOOKS];
    int bookCount = 0;
    int choice;

    // Load library from file at the start
    loadLibraryFromFile(library, &bookCount);

    do {
        // Display menu
        printf("\nLIBRARY MANAGEMENT SYSTEM:\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Remove Book\n");
        printf("0. Exit\n");

        // Get user choice
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform action based on user choice
        switch (choice) {
            case 1:
                addBook(library, &bookCount);
                break;
            case 2:
                displayBooks(library, bookCount);
                break;
            case 3:
                searchBook(library, bookCount);
                break;
            case 4:
                removeBook(library, &bookCount);
                break;
            case 0:
                printf("Exiting the program\n");
                // Save library to file before exiting
                saveLibraryToFile(library, bookCount);
                break;
            default:
                printf("Invalid Choice\n");
        }
    } while (choice != 0);

    return 0;
}

// Function to add a book to the library
void addBook(struct Book library[], int *bookCount) {
    if (*bookCount < MAX_BOOKS) {
        struct Book newBook;

        // Input book details
        printf("Enter book title: ");
        scanf(" %[^\n]", newBook.title);

        printf("Enter book author: ");
        scanf(" %[^\n]", newBook.author);

        printf("Enter publication year: ");
        scanf("%d", &newBook.year);

        // Add the new book to the library
        library[*bookCount] = newBook;
        (*bookCount)++;

        printf("Book added\n");

        // Save library to file after adding a book
        saveLibraryToFile(library, *bookCount);
    } else {
        printf("Maximum book limit reached\n");
    }
}

// Function to display all books in the library
void displayBooks(const struct Book library[], int bookCount) {
    if (bookCount > 0) {
        printf("\nLIST OF BOOKS:\n");
        for (int i = 0; i < bookCount; ++i) {
            printf("Title: %s\nAuthor: %s\nYear: %d\n\n",
                   library[i].title, library[i].author, library[i].year);
        }
    } else {
        printf("No books in the library.\n");
    }
}

// Function to search for a book by title
void searchBook(const struct Book library[], int bookCount) {
    if (bookCount > 0) {
        char searchTitle[50];
        int found = 0;

        // Input title to search
        printf("Enter the title of the book to search: ");
        scanf(" %[^\n]", searchTitle);

        // Search for the book in the library
        for (int i = 0; i < bookCount; ++i) {
            if (strcmp(library[i].title, searchTitle) == 0) {
                found = 1;
                printf("\nBook found:\n");
                printf("Title: %s\nAuthor: %s\nYear: %d\n\n",
                       library[i].title, library[i].author, library[i].year);
                break;
            }
        }

        if (!found) {
            printf("Book with title \"%s\" not found.\n", searchTitle);
        }
    } else {
        printf("No books in the library.\n");
    }
}

// Function to remove a book from the library
void removeBook(struct Book library[], int *bookCount) {
    if (*bookCount > 0) {
        char removeTitle[50];
        int found = 0;

        // Input title to remove
        printf("Enter the title of the book to remove: ");
        scanf(" %[^\n]", removeTitle);

        // Find the book in the library
        for (int i = 0; i < *bookCount; ++i) {
            if (strcmp(library[i].title, removeTitle) == 0) {
                found = 1;

                // Remove the book by shifting elements
                for (int j = i; j < (*bookCount - 1); ++j) {
                    library[j] = library[j + 1];
                }

                (*bookCount)--;
                printf("\nBook removed.\n");

                // Save library to file after removing a book
                saveLibraryToFile(library, *bookCount);

                break;
            }
        }

        if (!found) {
            printf("Book with title \"%s\" not found.\n", removeTitle);
        }
    }
}

// Function to save library to file
void saveLibraryToFile(const struct Book library[], int bookCount) {
    FILE *file = fopen("library.txt", "w");

    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < bookCount; ++i) {
        fprintf(file, "%s\n%s\n%d\n",
                library[i].title, library[i].author, library[i].year);
    }

    fclose(file);
}

// Function to load library from file
void loadLibraryFromFile(struct Book library[], int *bookCount) {
    FILE *file = fopen("library.txt", "r");

    if (file == NULL) {
        printf("No existing library file.\n");
        return;
    }

    while (*bookCount < MAX_BOOKS &&
           fscanf(file, " %[^\n]\n%[^\n]\n%d\n",
                  library[*bookCount].title,
                  library[*bookCount].author,
                  &library[*bookCount].year) == 3) {
        (*bookCount)++;
    }

    fclose(file);
}
