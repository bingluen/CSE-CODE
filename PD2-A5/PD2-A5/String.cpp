// Member-function definitions for class String.
#include <iostream>
#include <iomanip>
using namespace std;
#include "String.h" // include definition of class String 

String::String( const char *s, unsigned int n )
   : size( strlen( s ) )
{
   if( n < size )
      size = n;
   capacity = size;

   sPtr = new char[ capacity ];

   if( size > 0 )
      for( unsigned int i = 0; i < size; i++ )
         sPtr[ i ] = s[ i ];
}

// destructor
String::~String()
{
   delete [] sPtr;
} // end destructor

char* String::begin()
{
   return sPtr;
}

unsigned int String::getSize() const
{
   return size;
}

void String::clear()
{
   size = 0;
}

// overloaded output operator
ostream &operator<<( ostream &output, const String &s )
{
   for( unsigned int i = 0; i < s.size; i++ )
      output << s.sPtr[ i ];

   return output; // enables cascading
} // end function operator<<

/* Assigment 5 - string implement */

String::String(const String &str)
{
	// Constructs a copy of str.
}

const String & String::operator = (const String &)
{
	// assignment operator
}

bool String::operator == (const String &) const
{
	// test s1 == s2
}

char & String::operator[](unsigned int)
{
	// subscript operator (modifiable lvalue)
}

void String::resize(unsigned int n)
{
	// Resizes the string to a length of n characters.
	// If n is smaller than the current string length,
	// the current value is shortened to its first n character,
	// removing the characters beyond the nth.
	// If n is greater than the current string length,
	// the current content is extended by inserting at the end
	// as many characters as needed to reach a size of n.
	// The new elements are initialized as copies of null characters.
}

void String::reserve(unsigned int n = 0)
{
	// Requests that the string capacity be enough to contain n characters.
	// If n is greater than the current string capacity,
	// the function causes the container to reallocate its storage increasing its capacity to n.
	// In all other cases, the function call does not cause a reallocation and
	// the string capacity is not affected.
}


String& String::assign(char *first, char *last)
{
	// Copies the sequence of characters in the range [first,last), in the same order. Returns *this
}


String& String::erase(unsigned int pos = 0, unsigned int len = npos)
{
	// Erases the portion of the string value that begins at the character position pos and spans len characters
	// (or until the end of the string, if either the content is too short or if len is string::npos).
	// Returns *this
}

char* String::erase(char *first, char *last)
{
	// Erases the sequence of characters in the range [first,last).
	// This effectively reduces the container size by the number of elements removed.
	// Relocates all the characters after the segment erased to their new positions.
	// Returns a pointer referring to the character that now occupies the position of the first character erased,
	// or string::end if no such character exists.

}

unsigned int String::find(char c, unsigned int pos) const
{
	// Searches the string for the first occurrence of the character specified by its arguments.
	// Returns the position of the first match. If no matches were found, the function returns string::npos.
}

String String::substr(unsigned int pos, unsigned int len) const
{
	// Returns a newly constructed string object with its value initialized to a copy of a substring of this object.
	// The substring is the portion of the object that starts at character position pos and spans len characters
	// (or until the end of the string, whichever comes first).

}
