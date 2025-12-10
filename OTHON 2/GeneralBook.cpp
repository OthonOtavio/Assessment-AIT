#include "GeneralBook.h"

GeneralBook::GeneralBook(string n, string a, string id, bool avail, string date)
    : name(n), author(a), identifier(id), isOnShelf(avail), entryDate(date), valid(true) {
    validateBook();
}

GeneralBook::~GeneralBook() {}

string GeneralBook::getId() const {
    return identifier;
}

string GeneralBook::getTitle() const {
    return name;
}

bool GeneralBook::available() const {
    return isOnShelf && valid;
}

bool GeneralBook::isValid() const {
    return valid;
}

void GeneralBook::validateBook() {
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

void GeneralBook::displayDetails() const {
    if (!valid) {
        cout << "INVALID BOOK RECORD\n";
    }
    cout << "Title: " << name << "\n";
    cout << "Author: " << (author.empty() ? "<empty>" : author) << "\n";
    cout << "ISBN: " << identifier << "\n";
    cout << "Available: " << (isOnShelf ? "Yes" : "No") << "\n";
    cout << "Entry Date: " << entryDate << "\n";
}

void GeneralBook::borrowBook() {
    if (!valid) {
        cout << "Cannot borrow \"" << name << "\" because the data is invalid.\n";
        return;
    }
    if (isOnShelf) {
        isOnShelf = false;
        cout << "Book borrowed: " << name << "\n";
    } else {
        cout << "Currently unavailable: " << name << "\n";
    }
}

void GeneralBook::returnBook() {
    if (!valid) {
        cout << "Cannot return \"" << name << "\" because the data is invalid.\n";
        return;
    }
    if (!isOnShelf) {
        isOnShelf = true;
        cout << "Returned: " << name << "\n";
    } else {
        cout << "This book was already on the shelf: " << name << "\n";
    }
}

ShelfBook::ShelfBook(string n, string a, string id, bool avail, string date, string shelf)
    : GeneralBook(n, a, id, avail, date), shelfCode(shelf) {
}

void ShelfBook::displayDetails() const {
    GeneralBook::displayDetails();
    cout << "Shelf Code: " << shelfCode << "\n";
}

OnlineBook::OnlineBook(string n, string a, string id, bool avail, string date, string expiry)
    : GeneralBook(n, a, id, avail, date), licenseExpiry(expiry) {
}

void OnlineBook::displayDetails() const {
    GeneralBook::displayDetails();
    cout << "License Expiry: " << licenseExpiry << "\n";
}

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

BookLibrary::~BookLibrary() {
    for (auto b : records) {
        delete b;
    }
}

void BookLibrary::addBook(GeneralBook* b) {
    records.push_back(b);
}

void BookLibrary::deleteBook(const string& codeISBN) {
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it)->getId() == codeISBN) {
            delete *it;
            records.erase(it);
            cout << "Book removed from library.\n";
            return;
        }
    }
    cout << "Book not found to delete.\n";
}

GeneralBook* BookLibrary::findBook(const string& id) {
    for (auto b : records) {
        if (b->getId() == id) {
            return b;
        }
    }
    return nullptr;
}

void BookLibrary::showAvailableBooks() const {
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

void BookLibrary::showAllBooks() const {
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
