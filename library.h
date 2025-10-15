#ifndef LIBRARY_H
#define LIBRARY_H

#include "book.h"
#include <vector>

class Library {
private: 
    std::vector<Book> books;
public:
    bool addBook(Book& myBook);

    void borrowBook(Book& myBook);
    void borrowBook(std::vector<Book> borrowMany);

    void returnBook(Book& myBook);

    std::string availableBooks();
    void availableBooks(Book& myBook);

    void borrowedBooks();

    int numberOfBooks();
    int numberOfAvailableBooks();
    std::vector<std::string> allBooks();
};

#endif