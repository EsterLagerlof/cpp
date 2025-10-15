#include "book.h"
#include <iostream>


Book::Book() : title("Unknown"), author("Unknown"), available(true) {}

Book::Book(std::string t, std::string a, bool av) : title(t), author(a), available(av){}

std::string Book::getTitle() {
    return title;
}

std::string Book::getAuthor() {
    return author;
}

bool Book::getAvailability() {
    return available;
}

void Book::display() {
    std::cout << "  Title:  " << getTitle() 
                << "\n  Author: " << getAuthor()
                << "\n  Status: " << ((getAvailability()) ? "Available" : "Borrowed")
                << std::endl;
    std::cout << std::endl;
}

void Book::borrow() {
    if (!getAvailability()) {
        std::cout << std::endl;
        std::cout << "'" << getTitle() << "' is unfortunately already borrowed." << std::endl; 
    } else if (getAvailability()){
        available = false;
        std::cout << "\n" << "'" << getTitle() << "' is now borrowed!" << std::endl;
    }
}

void Book::returnB() {
    if (!getAvailability()) {
        available = true;
        std::cout << std::endl;
        std::cout << "'" << getTitle() << "' is now returned!" << std::endl; 
    } else if (getAvailability()) {
        std::cout << std::endl;
        std::cout << "We already have a returned copy of '" << getTitle() << "'." << std::endl;
    }
}

