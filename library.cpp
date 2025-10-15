#include <iostream>
#include "library.h"

bool Library::addBook(Book& myBook) {
    bool bookExists = false;
    for (Book& newBook : books) {
        if (newBook.getTitle() == myBook.getTitle()) {
            bookExists = true;
            std::cout << "\nWe already have a book called '" << myBook.getTitle() << "' in our system. We don't take duplicates I'm afraid.\n";
        }
    }
    if (!bookExists) {
        books.push_back(myBook);
    }
    return bookExists;
}

void Library::borrowBook(Book& myBook) {
    bool bookExists = false;
    for (Book& newBook : books) {
        if (newBook.getTitle() == myBook.getTitle()) {
            newBook.borrow();
            bookExists = true;
        }
    }
    if (!bookExists) {
        std::cout << "\nUnfortunately we don't have the book '" << myBook.getTitle() << "' in our system.";
        std::cout << std::endl;
    }
}

void Library::borrowBook(std::vector<Book> borrowMany) {
    
    for (int i = 0; i < borrowMany.size(); i++) {
        bool bookExists = false;
        for (int y = 0; y < books.size(); y++) {
            if (borrowMany[i].getTitle() == books[y].getTitle()) {
                books[y].borrow();
                bookExists = true;
            }
        }
        if (!bookExists) {
            std::cout << "\nUnfortunately we don't have the book '" << borrowMany[i].getTitle() << "' in our system.";
            std::cout << std::endl;
        }
    }
}

void Library::returnBook(Book& myBook) {
    int count = 0;
    for (Book& newBook : books) {
        if (newBook.getTitle() == myBook.getTitle()) {
            newBook.returnB();
            count++;
        }
    }
    if (count == 0){
        std::cout << std::endl;
        std::cout << "Unfortunately we don't have the book '" << myBook.getTitle() << "' in our system." << std::endl;
    }
}

std::string Library::availableBooks() {
    std::string title;
    std::cout << "Here are our available books: \n" << std::endl;
    for (Book& myBook : books) {
        if (myBook.getAvailability() == true) {
            myBook.display();
            title = myBook.getTitle();
        }
    }
    return title;
}

void Library::availableBooks(Book& myBook) {
    int count = 0;
    for (Book& newBook : books) {
        if (newBook.getTitle() == myBook.getTitle()) {
            count++;
            if (newBook.getAvailability() == true){
                newBook.display();
                count++;
            }
        }
    }
    if (count == 0){
        std::cout << "Unfortunately we don't have the book '" << myBook.getTitle() << "' in our system." << std::endl;
    }
    if (count == 1){
        std::cout << "'" << myBook.getTitle() << "' is currenlty not available." << std::endl;
    }
}

void Library::borrowedBooks() {
    std::cout << "\nHere are our currently borrowed books: \n" << std::endl;
    for (Book& myBook : books) {
        if (myBook.getAvailability() == false) {
            myBook.display();
        }
    }
}

int Library::numberOfBooks() {
    int numberOfBooks = 0;
    for (Book& myBook : books) {
        numberOfBooks ++;
    }
    return numberOfBooks;
}

int Library::numberOfAvailableBooks() {
    int numberOfAvailableBooks = 0;
    for (Book& myBook : books) {
        if (myBook.getAvailability() == true) {
            numberOfAvailableBooks++;
        }
    }
    return numberOfAvailableBooks;
}

std::vector<std::string> Library::allBooks() {
    std::vector<std::string> writeBooks;
        for (Book& myBook : books){ // student = maja, student = kajsa
                writeBooks.push_back(myBook.getTitle());
                writeBooks.push_back(",");
                writeBooks.push_back(myBook.getAuthor());
                writeBooks.push_back(",");
                writeBooks.push_back(((myBook.getAvailability()) ? "Available" : "Borrowed"));
                writeBooks.push_back("\n");
        }
    return writeBooks;
}

