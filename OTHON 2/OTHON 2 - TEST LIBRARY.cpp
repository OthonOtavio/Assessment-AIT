#include <iostream>
#include <string>
#include "GeneralBook.h"
using namespace std;

int main() {
    BookLibrary myLibrary;

    ShelfBook* correct1 = new ShelfBook(
        "Homo Deus", "Yuval Noah Harari",
        "9780062464316", true, "2025-11-01", "A2");

    ShelfBook* correct2 = new ShelfBook(
        "Rich Dad, Poor Dad", "Robert Kiyosaki",
        "9781612680194", true, "2025-11-21", "B8");

    ShelfBook* correct3 = new ShelfBook(
        "Atomic Habits", "James Clear",
        "9780735211292", true, "2025-11-01", "C1");

    myLibrary.addBook(correct1);
    myLibrary.addBook(correct2);
    myLibrary.addBook(correct3);

    myLibrary.addBook(new OnlineBook(
        "Sapiens - A Brief History of Humankind", "Yuval Noah Harari",
        "9780062316097", true, "2025-11-21", "2027-05-23"));

    myLibrary.addBook(new OnlineBook(
        "Educated", "Tara Westover",
        "9780399590504", true, "2025-11-21", "2028-01-01"));

    myLibrary.addBook(new ShelfBook(
        "Homo Deus (Bad)", "Yuval Noah Harari",
        "97800X2464316", true, "11-01-2025", "Z9"));

    myLibrary.addBook(new ShelfBook(
        "Rich Dad, Poor Dad (Bad)", "",
        "9781612680194", true, "2025/11/21", "Y7"));

    myLibrary.addBook(new OnlineBook(
        "Atomic Habits (Bad)", "James Clear",
        "ABC5211292", true, "2025-11", "2030-01-01"));

    cout << "-- Othon's A3 Library Test Application --\n";

    string choice;
    string inputId;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Show available books\n";
        cout << "2. Borrow book\n";
        cout << "3. Return book\n";
        cout << "4. Delete book from library\n";
        cout << "5. Sort test - Ascending order array\n";
        cout << "6. Sort test - Descending order array\n";
        cout << "7. Sort test - Mixed order array\n";
        cout << "8. Show all books (including invalid)\n";
        cout << "0. Quit\n";
        cout << "Your selection: ";
        getline(cin, choice);

        if (choice == "0") {
            cout << "Finished.\n";
            break;
        }
        else if (choice == "1") {
            myLibrary.showAvailableBooks();
        }
        else if (choice == "2") {
            cout << "Please enter ISBN to borrow: ";
            getline(cin, inputId);
            GeneralBook* b = myLibrary.findBook(inputId);
            if (b) {
                b->borrowBook();
            } else {
                cout << "Book not found.\n";
            }
        }
        else if (choice == "3") {
            cout << "Please enter ISBN to return: ";
            getline(cin, inputId);
            GeneralBook* b = myLibrary.findBook(inputId);
            if (b) {
                b->returnBook();
            } else {
                cout << "Book not found.\n";
            }
        }
        else if (choice == "4") {
            cout << "Please enter ISBN to delete: ";
            getline(cin, inputId);
            myLibrary.deleteBook(inputId);
        }
        else if (choice == "5") {
            GeneralBook* asc[3] = { correct3, correct1, correct2 };
            cout << "\nArray 1 - Ascending order ADDED (before sort):\n";
            for (int i = 0; i < 3; ++i) {
                cout << "- " << asc[i]->getTitle() << "\n";
            }
            sortByTitleAscending(asc, 3);
            cout << "Array 1 - After sort (should stay ascending):\n";
            for (int i = 0; i < 3; ++i) {
                cout << "- " << asc[i]->getTitle() << "\n";
            }
        }
        else if (choice == "6") {
            GeneralBook* desc[3] = { correct2, correct1, correct3 };
            cout << "\nArray 2 - Descending order ADDED (before sort):\n";
            for (int i = 0; i < 3; ++i) {
                cout << "- " << desc[i]->getTitle() << "\n";
            }
            sortByTitleAscending(desc, 3);
            cout << "Array 2 - After sort (ascending result):\n";
            for (int i = 0; i < 3; ++i) {
                cout << "- " << desc[i]->getTitle() << "\n";
            }
        }
        else if (choice == "7") {
            GeneralBook* mixed[3] = { correct1, correct2, correct3 };
            cout << "\nArray 3 - Mixed order ADDED (before sort):\n";
            for (int i = 0; i < 3; ++i) {
                cout << "- " << mixed[i]->getTitle() << "\n";
            }
            sortByTitleAscending(mixed, 3);
            cout << "Array 3 - After sort (ascending result):\n";
            for (int i = 0; i < 3; ++i) {
                cout << "- " << mixed[i]->getTitle() << "\n";
            }
        }
        else if (choice == "8") {
            myLibrary.showAllBooks();
        }
        else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
