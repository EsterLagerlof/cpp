#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
private:
    std::string title;
    std::string author;
    bool available = true;

public:
    Book();
    Book(std::string t, std::string a, bool av);
    std::string getTitle();
    std::string getAuthor();
    bool getAvailability();
    void display();
    void borrow();
    void returnB();
};

#endif