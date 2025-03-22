#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Book {
public:
    int id;
    string title, author;

    Book() {} // Default constructor for vector operations

    Book(int i, string t, string a) : id(i), title(t), author(a) {}

    void display() const {
        cout << "ID: " << id << " | Title: " << title << " | Author: " << author << endl;
    }
};

class Library {
private:
    vector<Book> books;
    const string filename = "library_data.txt";

public:
    Library() { loadFromFile(); }

    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
        saveToFile();
        cout << "Book added successfully!\n";
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books in the library.\n";
            return;
        }
        for (const auto &book : books)
            book.display();
    }

    void searchBook(int id) {
        for (const auto &book : books) {
            if (book.id == id) {
                cout << "Book found:\n";
                book.display();
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void deleteBook(int id) {
        bool found = false;
        vector<Book> updatedBooks;
        for (const auto &book : books) {
            if (book.id == id) {
                found = true;
            } else {
                updatedBooks.push_back(book);
            }
        }
        if (found) {
            books = updatedBooks;
            saveToFile();
            cout << "Book deleted successfully!\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    void saveToFile() {
        ofstream file(filename);
        for (const auto &book : books)
            file << book.id << "|" << book.title << "|" << book.author << "\n"; // Use "|" as delimiter
        file.close();
    }

    void loadFromFile() {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, title, author;
            getline(ss, idStr, '|'); 
            getline(ss, title, '|'); 
            getline(ss, author);

            if (!idStr.empty()) {
                books.push_back(Book(stoi(idStr), title, author));
            }
        }
        file.close();
    }
};

int main() {
    Library lib;
    int choice, id;
    string title, author;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Display Books\n3. Search Book\n4. Delete Book\n5. Exit\nChoice: ";
        cin >> choice;
        cin.ignore(); // Fix input issue

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore(); // Clears newline
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                lib.addBook(id, title, author);
                break;
            case 2:
                lib.displayBooks();
                break;
            case 3:
                cout << "Enter Book ID to search: ";
                cin >> id;
                lib.searchBook(id);
                break;
            case 4:
                cout << "Enter Book ID to delete: ";
                cin >> id;
                lib.deleteBook(id);
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
