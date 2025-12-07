#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// ===================== Base class =====================
class GeneralBook {
protected:
    string name;
    string author;
    string identifier;
    bool isOnShelf;
    string entryDate;
    bool valid;

public:
    GeneralBook(string n, string a, string id, bool avail, string date)
        : name(n), author(a), identifier(id), isOnShelf(avail), entryDate(date), valid(true) {
        validateBook();
    }

    virtual ~GeneralBook() {}

    string getId() const { return identifier; }
    string getTitle() const { return name; }
    bool available() const { return isOnShelf && valid; }
    bool isValid() const { return valid; }

    void validateBook() {
        valid = true;
        string errors = "";

        if (author.empty()) {
            errors += "Author Error: empty field. ";
            valid = false;
        }

        bool isbnNumeric = !identifier.empty();
        for (char c : identifier) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                isbnNumeric = false;
                break;
            }
        }
        if (!isbnNumeric) {
            errors += "ISBN Error: not numeric. ";
            valid = false;
        }

        if (entryDate.length() != 10 || entryDate[4] != '-' || entryDate[7] != '-') {
            errors += "Date Error: wrong format (expected YYYY-MM-DD). ";
            valid = false;
        }

        if (!errors.empty()) {
            cout << "[Validation] \"" << (name.empty() ? "No title" : name)
                << "\": " << errors << "\n";
        }
    }

    virtual void displayDetails() const {
        if (!valid) {
            cout << "INVALID BOOK RECORD\n";
        }
        cout << "Title: " << name << "\n";
        cout << "Author: " << (author.empty() ? "<empty>" : author) << "\n";
        cout << "ISBN: " << identifier << "\n";
        cout << "Available: " << (isOnShelf ? "Yes" : "No") << "\n";
        cout << "Entry Date: " << entryDate << "\n";
    }

    void borrowBook() {
        if (!valid) {
            cout << "Cannot borrow \"" << name << "\" because the data is invalid.\n";
            return;
        }
        if (isOnShelf) {
            isOnShelf = false;
            cout << "Book borrowed: " << name << "\n";
        }
        else {
            cout << "Currently unavailable: " << name << "\n";
        }
    }

    void returnBook() {
        if (!valid) {
            cout << "Cannot return \"" << name << "\" because the data is invalid.\n";
            return;
        }
        if (!isOnShelf) {
            isOnShelf = true;
            cout << "Returned: " << name << "\n";
        }
        else {
            cout << "This book was already on the shelf: " << name << "\n";
        }
    }
};

// ===================== ShelfBook =====================
class ShelfBook : public GeneralBook {
    string shelfCode;
public:
    ShelfBook(string n, string a, string id, bool avail, string date, string shelf)
        : GeneralBook(n, a, id, avail, date), shelfCode(shelf) {
    }

    void displayDetails() const override {
        GeneralBook::displayDetails();
        cout << "Shelf Code: " << shelfCode << "\n";
    }
};

// ===================== OnlineBook =====================
class OnlineBook : public GeneralBook {
    string licenseExpiry;
public:
    OnlineBook(string n, string a, string id, bool avail, string date, string expiry)
        : GeneralBook(n, a, id, avail, date), licenseExpiry(expiry) {
    }

    void displayDetails() const override {
        GeneralBook::displayDetails();
        cout << "License Expiry: " << licenseExpiry << "\n";
    }
};

// ===================== Utility: simple bubble sort =====================
void sortByTitleAscending(GeneralBook* arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j]->getTitle() > arr[j + 1]->getTitle()) {
                GeneralBook* tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

// ===================== Library manager =====================
class BookLibrary {
    vector<GeneralBook*> records;

public:
    ~BookLibrary() {
        for (auto b : records) {
            delete b;
        }
    }

    void addBook(GeneralBook* b) {
        records.push_back(b);
    }

    void deleteBook(const string& codeISBN) {
        for (auto it = records.begin(); it != records.end(); ++it) {
            if ((*it)->getId() == codeISBN) {
                delete* it;
                records.erase(it);
                cout << "Book removed from library.\n";
                return;
            }
        }
        cout << "Book not found to delete.\n";
    }

    GeneralBook* findBook(const string& id) {
        for (auto b : records) {
            if (b->getId() == id) {
                return b;
            }
        }
        return nullptr;
    }

    void showAvailableBooks() const {
        cout << "\n=== Available in library ===\n";
        bool any = false;
        for (auto b : records) {
            if (b->available()) {
                b->displayDetails();
                cout << "----------------------\n";
                any = true;
            }
        }
        if (!any) {
            cout << "No available books at the moment.\n";
        }
    }

    void showAllBooks() const {
        cout << "\n=== All books (valid and invalid) ===\n";
        if (records.empty()) {
            cout << "No books in the system.\n";
            return;
        }
        for (auto b : records) {
            b->displayDetails();
            cout << "----------------------\n";
        }
    }
};

// ===================== main =====================
int main() {
    BookLibrary myLibrary;

    // ----- Correct books (will be used for sorting tests) -----
    ShelfBook* correct1 = new ShelfBook(
        "Homo Deus", "Yuval Noah Harari",
        "9780062464316", true, "2025-11-01", "A2");

    ShelfBook* correct2 = new ShelfBook(
        "Rich Dad, Poor Dad", "Robert Kiyosaki",
        "9781612680194", true, "2025-11-21", "B8");

    ShelfBook* correct3 = new ShelfBook(
        "Atomic Habits", "James Clear",
        "9780735211292", true, "2025-11-01", "C1");

    // Add correct books to main library
    myLibrary.addBook(correct1);
    myLibrary.addBook(correct2);
    myLibrary.addBook(correct3);

    // Extra correct online books for normal menu use
    myLibrary.addBook(new OnlineBook(
        "Sapiens - A Brief History of Humankind", "Yuval Noah Harari",
        "9780062316097", true, "2025-11-21", "2027-05-23"));

    myLibrary.addBook(new OnlineBook(
        "Educated", "Tara Westover",
        "9780399590504", true, "2025-11-21", "2028-01-01"));

    // ----- Incorrect books for validation tests (NOT used in sorting) -----
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
            }
            else {
                cout << "Book not found.\n";
            }
        }
        else if (choice == "3") {
            cout << "Please enter ISBN to return: ";
            getline(cin, inputId);
            GeneralBook* b = myLibrary.findBook(inputId);
            if (b) {
                b->returnBook();
            }
            else {
                cout << "Book not found.\n";
            }
        }
        else if (choice == "4") {
            cout << "Please enter ISBN to delete: ";
            getline(cin, inputId);
            myLibrary.deleteBook(inputId);
        }
        else if (choice == "5") {
            // Ascending array: already in A-Z (Atomic, Homo, Rich)
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
            // Descending array: Rich, Homo, Atomic
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
            // Mixed array: Homo, Rich, Atomic
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
