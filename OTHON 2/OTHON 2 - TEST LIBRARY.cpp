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
            getline(cin,
