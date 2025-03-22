#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Book {
public:
    string title, author;
    int id;

    Book(int i, string t, string a) : id(i), title(t), author(a) {}

    void display() {
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
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) {
                books.erase(it);
                saveToFile();
                cout << "Book deleted successfully!\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void saveToFile() {
        ofstream file(filename);
        for (const auto &book : books)
            file << book.id << " " << book.title << " " << book.author << "\n";
        file.close();
    }

    void loadFromFile() {
        ifstream file(filename);
        int id; string title, author;
        while (file >> id >> ws && getline(file, title, ' ') && getline(file, author))
            books.push_back(Book(id, title, author));
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
        
        switch (choice) {
            case 1:
                cout << "Enter Book ID, Title, Author: ";
                cin >> id >> ws;
                getline(cin, title);
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
