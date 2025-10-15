#include <iostream>
#include <fstream> //for IO
#include <sstream> //for csv
#include <limits> // for cin.ignore()
#include "library.h"

using namespace std;

// To compile on mac, use: g++ -std=c++14 main.cpp library.cpp book.cpp
// ./a.out

int main() {

    // Read file
    ifstream bookFile("library.csv"); //bookFile name of file
    string line = "";

    if (!bookFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1; // Exit if file cannot be opened
    }

    string readTitle;
    string readAuthor;
    string readStatus;
    bool status;
    Library library;

    while(getline(bookFile, line)){ //Looping through all lines in the file

        stringstream lineStream(line);

        getline(lineStream, readTitle, ',');
        getline(lineStream, readAuthor, ',');
        getline(lineStream, readStatus, ',');
        if (readStatus == "Available"){
            status = true;
        } else {status = false;}
        Book book(readTitle, readAuthor, status);
        library.addBook(book);
        line.clear();
    }
    
    bookFile.close();
    
    int choose;
    string title;
    string author;
    int number;
    vector<Book> myBooks;

    cout << "\nWelcome to Ester's Library! What can I help you with today?" << endl;

    while(true){
        cout << "\n1. Add a book to the library\n2. Lend a book\n3. Return a book\n4. View available books\n5. Exit" << endl;
        cout << "(Choose 1-5): ";
        cin >> choose;

        while (cin.fail() || choose < 1 || choose > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter an integer between 1 and 5: ";
            cin >> choose;
        }

        // ADD A BOOK
        if (choose == 1){
            cout << "\nWhich book would you like to add to our collection? \nTitle: ";
            cin >> ws;
            getline(cin, title);
            cout << "Author: ";    
            cin >> ws;      
            getline(cin, author);          
            Book book(title, author, true);
            bool bookInLibrary = library.addBook(book);

            //if the book does not already exist in the library it is added
            if (!bookInLibrary) {
                cout << "\n'" << book.getTitle() << "'" << " added to the library!" << endl;
            }
        }

        // LEND A BOOK
        if (choose == 2){
            cout << endl;
            // as long as there are available books for lending
            if (library.numberOfAvailableBooks() != 0){ 
                library.availableBooks();

                if (library.numberOfAvailableBooks() == 1) {
                    cout << "\nWould you like to borrow this book?\n(1=Yes/0=No): ";
                    cin >> number;
                    while (cin.fail() || number > 1 || number < 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nInvalid input. Please enter 1 if you would like to borrow this book, or 0 if you want to go back to the menu: ";
                        cin >> number;
                    }
                    if (number == 1) {
                        title = library.availableBooks();
                        Book book(title, author, true);
                        library.borrowBook(book);
                    } else {
                        cout << "";
                    }
                    
                } else {
                    cout << "\nHow many of these books would you like to lend? (enter in digits) ";
                    cin >> number;

                    // if number is a non integer input
                    while (cin.fail() || number > library.numberOfAvailableBooks() || number < 0) { 
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\nInvalid input. Please enter an integer between 1 and " << library.numberOfAvailableBooks() << ", or 0 if you want to go back to the menu: ";
                        cin >> number;
                    }

                    // if they only want to borrow one book
                    if (number == 1){ 
                        cout << "\nWhich book would you like to lend?" << endl;
                        cout << "Title: ";
                        cin >> ws;
                        getline(cin, title);
                        Book book(title, author, true);
                        library.borrowBook(book);
                    }

                    // if they want to borrow multiple
                    if (number > 1 & number <= library.numberOfAvailableBooks()) { 
                        cout << "\nWhich books would you like to lend?" << endl;

                        for (int i = 1; i <= number; i++) {
                            cout << "\nTitle: ";
                            cin >> ws;
                            getline(cin, title);
                            Book book(title, author, true);
                            myBooks.push_back(book);
                        }

                        library.borrowBook(myBooks);
                        myBooks.clear();
                    }
                }
            } else {
                cout << "No available books." << endl;
            }
            // cout << endl;
            // cout << "Is there anything else I can help you with?" << endl;
        }

        // RETURN A BOOK
        if (choose == 3){
            library.borrowedBooks();
            cout << "\nWhich book would you like to return? \nTitle: ";
            cin >> ws;
            getline(cin, title);
            Book book(title, author, true);
            library.returnBook(book);     
            // cout << endl;
            // cout << "Is there anything else I can help you with?" << endl;      
        }

        // VIEW AVAILABLE BOOKS
        if (choose == 4){

            // if there are no available books
            if (library.numberOfAvailableBooks() == 0) {
                cout << "\nNo available books." << endl;
            } 
            
            // as long as there are any available books
            else { 
                cout << "\nWould you like to \n1. View all available books \n2. View a specific book" << endl;
                cout << "(Choose 1-2): ";
                cin >> number;

                // if input is invalid
                while (cin.fail() || number < 1 || number > 2) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nInvalid input. Please enter an integer between 1 and 2: ";
                    cin >> number;
                }

                if (number == 1) {
                    cout << endl;
                    library.availableBooks();
                    cout << "\nPress any key followed by enter to go back to menu" << endl;
                    cin >> title;
                }

                if (number == 2) {
                    cout << "\nWhich book would you like to view the details of?" << endl;
                    cout << "Title: ";
                    cin >> ws;
                    getline(cin, title);
                    Book book(title, author, true);
                    cout << endl;
                    library.availableBooks(book);
                    cout << "\nPress any key followed by enter to go back to menu" << endl;
                    cin >> title;
                }
            }
        }

        // EXIT
        if (choose == 5){
            cout << "\nHave a nice day!\n" << endl;
            break;
        }
        cout << "\nIs there anything else I can help you with?" << endl;
    }

    // write all the books in the library to a file
    string filename = "library.csv";
    ofstream outFile(filename); //create a text file
    
    if (outFile.is_open()){
        for (int i = 0; i < library.numberOfBooks()*6; i++){
                outFile << library.allBooks()[i];
        }
        outFile.close();
    }
    else{
        cerr << "Difficulty saving the books to a file." << endl;
    }

    return 0;
}