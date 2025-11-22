#include <iostream>
#include <string>
using namespace std;

class BookRecord {
private:
    string name;
    string author;
    string identifier;
    bool inLibrary;
    string entryDate;

public:
    BookRecord(string n, string a, string id, bool available, string date)
        : name(n), author(a), identifier(id), inLibrary(available), entryDate(date) {
    }

    string getIdentifier() const {
        return identifier;
    }

    bool isAvailable() const {
        return inLibrary;
    }

    void takeBook() {
        if (inLibrary) {
            inLibrary = false;
            cout << "This book has been borrowed by you: " << name << endl;
        }
        else {
            cout << "This book is not available: " << name << endl;
        }
    }

    void showBook() const {
        cout << "Name: " << name << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << identifier << endl;
        cout << "Available: " << (inLibrary ? "Yes" : "No") << endl;
        cout << "Added on: " << entryDate << endl;
    }
};

int findBook(BookRecord arr[], int count, const string& id) {
    for (int i = 0; i < count; i++) {
        if (arr[i].getIdentifier() == id) {
            return i;
        }
    }
    return -1;
}

int main() {
    const int BookCount = 5;
    BookRecord collection[BookCount] = {
        BookRecord("Homo Deus", "Yuval Noah Harari", "9780062464316", true, "2025-11-01"),
        BookRecord("Rich Dad Poor Dad", "Robert Kiyosaki", "9781612680194", true, "2025-11-01"),
        BookRecord("Atomic Habits", "James Clear", "9780735211292", true, "2025-11-01"),
        BookRecord("Sapiens: A Brief History of Humankind", "Yuval Noah Harari", "9780062316097", true, "2025-11-01"),
        BookRecord("Educated", "Tara Westover", "9780399590504", true, "2025-11-01")
    };

    cout << "Othon's Library\n";
    string userIsbn;

    while (true) {
        cout << "Enter the ISBN number to borrow a book or type 0 to quit the system: ";
        getline(cin, userIsbn);

        if (userIsbn == "0") {
            cout << "System is shuting down.\n";
            break;
        }

        int index = findBook(collection, BookCount, userIsbn);
        if (index == -1) {
            cout << "The book was not found.\n";
        }
        else {
            collection[index].takeBook();
        }
    }

    return 0;
}
