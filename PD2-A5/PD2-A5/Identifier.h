// Identifier class definition
#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "String.h" // String class definition

class Identifier : public String
{
public:
   Identifier( const char * = "" ); // default constructor
   const Identifier &operator=( const String & ); // assignment operator
   bool keyword(); // check if the current identifier is a C++ keyword
};

#endif