#include "Mystring.h"
#include<cstring>
//no args constructor
Mystring::Mystring():str{nullptr}{
    str=new char[1];
    *str='\0';
}
//Destrucor
Mystring::~Mystring(){delete str;}

//Overloaded constructor
Mystring::Mystring (const char *s):str{nullptr}{
    if(s==nullptr){
        str=new char[1];
        *str='\0';}
    else{
        str=new char[std::strlen(s)+1];
        std::strcpy(str, s);
    }
}

//cc
Mystring::Mystring( const Mystring &source){

}

void display() const;
int get_length() const;
const char *get_str() const;
