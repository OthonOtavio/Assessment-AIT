#ifndef GENERALBOOK_H
#define GENERALBOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

class GeneralBook {
protected:
    string name;
    string author;
    string identifier;
    bool isOnShelf;
    string entryDate;
    bool valid;

public:
    GeneralBook(string n, string a, string id, bool avail, string date);
    virtual ~GeneralBook();

    string getId() const;
    string getTitle() const;
    bool available() const;
    bool isValid() const;

    void validateBook();
    virtual void displayDetails() const;
    void borrowBook();
    void returnBook();
};

class ShelfBook : public GeneralBook {
    string shelfCode;
public:
    ShelfBook(string n, string a, string id, bool avail, string date, string shelf);
    void displayDetails() const override;
};

class OnlineBook : public GeneralBook {
    string licenseExpiry;
public:
    OnlineBook(string n, string a, string id, bool avail, string date, string expiry);
    void displayDetails() const override;
};

void sortByTitleAscending(GeneralBook* arr[], int size);

class BookLibrary {
    vector<GeneralBook*> records;

public:
    ~BookLibrary();
    void addBook(GeneralBook* b);
    void deleteBook(const string& codeISBN);
    GeneralBook* findBook(const string& id);
    void showAvailableBooks() const;
    void showAllBooks() const;
};

#endif
