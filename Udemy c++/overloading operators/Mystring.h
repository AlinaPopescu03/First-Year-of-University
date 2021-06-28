#ifndef OVERLOADING_OPERATORS_MYSTRING_H
#define OVERLOADING_OPERATORS_MYSTRING_H
#include<iostream>


class Mystring {
private:
    char *str;//C-style string
public:
    Mystring();
    Mystring (const char *s);
    Mystring( const Mystring &source);
    ~Mystring();
    void display() const;
    int get_length() const;
    const char *get_str() const;

};


#endif //OVERLOADING_OPERATORS_MYSTRING_H
