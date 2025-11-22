#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class for books
class GeneralBook {
protected:
    string name, author, identifier;
    bool isOnShelf;
    string entryDate;

public:
    GeneralBook(string n, string a, string id, bool avail, string date)
        : name(n), author(a), identifier(id), isOnShelf(avail), entryDate(date) {
    }

    virtual ~GeneralBook() {}

    string getId() const { return identifier; }
    bool available() const { return isOnShelf; }

    virtual void displayDetails() const {
        cout << "Name: " << name << endl
            << "Author: " << author << endl
            << "ISBN: " << identifier << endl
            << "Available: " << (isOnShelf ? "Yes" : "No") << endl
            << "Entry Date: " << entryDate << endl;
    }

    void borrowBook() {
        if (isOnShelf) {
            isOnShelf = false;
            cout << "You've Borrowed the Book: " << name << endl;
        }
        else {
            cout << "Currently unavailable: " << name << endl;
        }
    }

    void returnBook() {
        isOnShelf = true;
        cout << "Returned: " << name << endl;
    }
};

// Derived class for shelf (physical) books
class ShelfBook : public GeneralBook {
    string shelfCode;
public:
    ShelfBook(string n, string a, string id, bool avail, string date, string shelf)
        : GeneralBook(n, a, id, avail, date), shelfCode(shelf) {
    }
    void displayDetails() const override {
        GeneralBook::displayDetails();
        cout << "Shelf Code: " << shelfCode << endl;
    }
};

// Derived class for online (digital) books
class OnlineBook : public GeneralBook {
    string licenseExpiry;
public:
    OnlineBook(string n, string a, string id, bool avail, string date, string expiry)
        : GeneralBook(n, a, id, avail, date), licenseExpiry(expiry) {
    }
    void displayDetails() const override {
        GeneralBook::displayDetails();
        cout << "License Expiry: " << licenseExpiry << endl;
    }
};

// Manager class
class BookLibrary {
    vector<GeneralBook*> records;
public:
    ~BookLibrary() { for (auto b : records) delete b; }

    void addBook(GeneralBook* b) { records.push_back(b); }

    GeneralBook* findBook(const string& id) {
        for (auto b : records)
            if (b->getId() == id) return b;
        return nullptr;
    }

    void showAvailableBooks() {
        cout << "\nBooks Available in library:\n";
        for (auto b : records)
            if (b->available()) {
                b->displayDetails();
                cout << "---------\n";
            }
    }
};

int main() {
    BookLibrary myLibrary;

    // Add books, classify some as shelf and some as online
    myLibrary.addBook(new ShelfBook("Homo Deus", "Yuval Noah Harari", "9780062464316", true, "2025-11-01", "A2"));
    myLibrary.addBook(new ShelfBook("Rich Dad Poor Dad", "Robert Kiyosaki", "9781612680194", true, "2025-11-01", "B8"));
    myLibrary.addBook(new ShelfBook("Atomic Habits", "James Clear", "9780735211292", true, "2025-11-01", "C1"));
    myLibrary.addBook(new OnlineBook("Sapiens: A Brief History of Humankind", "Yuval Noah Harari", "9780062316097", true, "2025-11-01", "2027-05-23"));
    myLibrary.addBook(new OnlineBook("Educated", "Tara Westover", "9780399590504", true, "2025-11-01", "2028-01-01"));

    cout << "Othon's Library\n";
    string choice, inputId;

    while (true) {
        cout << "\n1. Show available books\n2. Borrow a book\n3. Return a book\n0. Quit\nYour current selection: ";
        getline(cin, choice);
        if (choice == "0") {
            cout << "Finished.\n";
            break;
        }
        else if (choice == "1") {
            myLibrary.showAvailableBooks();
        }
        else if (choice == "2") {
            cout << "Please enter the ISBN number to borrow: ";
            getline(cin, inputId);
            GeneralBook* b = myLibrary.findBook(inputId);
            if (b) b->borrowBook();
            else cout << "The book was not found.\n";
        }
        else if (choice == "3") {
            cout << "Please enter the ISBN number to return a book: ";
            getline(cin, inputId);
            GeneralBook* b = myLibrary.findBook(inputId);
            if (b) b->returnBook();
            else cout << "The book was not found.\n";
        }
        else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
