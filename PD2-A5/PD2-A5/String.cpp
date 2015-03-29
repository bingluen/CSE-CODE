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

	//copy capacity & size
	this->capacity = str.capacity;
	this->size = str.size;

	//allocate memory
	this->sPtr = new char[capacity];

	//copy data from source
	memcpy(this->sPtr, str.sPtr, this->getSize() * sizeof(char));
}

const String & String::operator = (const String &right)
{
	// assignment operator

	//compare this->capacity and right.size, if right.size > this->capacity, call reserve
	if (right.size > this->capacity)
	{
		this->reserve(right.size);
	}

	//copy data
	memcpy(this->sPtr, right.sPtr, right.size);

	//reset size
	this->size = right.size;

	return *this;
}

bool String::operator == (const String &right) const
{
	// test s1 == s2
	if (!strcmp(this->sPtr, right.sPtr))
		return true;
	else
		return false;
}

char & String::operator[](unsigned int pos)
{
	// subscript operator (modifiable lvalue)
	
	//if out of bound, print error
	if (pos >= this->getSize())
	{
		cerr << "index " << pos << " out of bound " << endl;
		exit(0);
	}

	return this->sPtr[pos];
	
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

	//compare n and capacity, if n > capacity  call reserve
	if (n > capacity)
	{
		this->reserve(n);
	}

	//initialize new elements
	for (size_t i = this->getSize(); i < n; i++)
		this->sPtr[i] = '\0';

	//reset size
	this->size = n;

	
}

void String::reserve(unsigned int n)
{
	// Requests that the string capacity be enough to contain n characters.
	// If n is greater than the current string capacity,
	// the function causes the container to reallocate its storage increasing its capacity to n.
	// In all other cases, the function call does not cause a reallocation and
	// the string capacity is not affected.

	if (n > this->capacity)
	{
		//save memory address
		char* tempSPtr = sPtr;
		//reallocate memory
		this->sPtr = new char[n];
		//copy data
		memcpy(this->sPtr, tempSPtr, this->capacity * sizeof(char));

		//delete the old memory
		delete[] tempSPtr;

		//reset capacity
		this->capacity = n;
	}
}


String& String::assign(char *first, char *last)
{
	// Copies the sequence of characters in the range [first,last), in the same order. Returns *this

	unsigned int length;
	if ((length = (unsigned int)(last - first)) > strlen(first))
	{
		length = strlen(first);
	}
	this->resize(length);

	//copy data
	memcpy(this->sPtr, first, length);

	return *this;
}


String& String::erase(unsigned int pos, unsigned int len)
{
	// Erases the portion of the string value that begins at the character position pos and spans len characters
	// (or until the end of the string, if either the content is too short or if len is string::npos).
	// Returns *this

	//check length are reasonable, if not reset length
	unsigned int length;

	if (len + pos >= this->getSize())
		length = this->getSize() - pos;
	else
		length = len;

	//move character to erase
	/*
		use memcpy is more efficiently than memmove, but is not safe on follow case:
		length = 11
		index    0 1 2 3 4 5 6 7 8 9 10
		sPtr = [ a b c d e f g h i j k ]
					 |	   |
					pos  pos+len
		memcpy may lead data damage

	*/
	memmove(this->sPtr + pos, this->sPtr + pos + length, this->getSize() - pos - length);

	//reset size
	this->size -= length;

	//clear memoery
	memset(this->sPtr + this->size - 1, 0, this->capacity - this->size);

	

	return *this;
}

char* String::erase(char *first, char *last)
{
	// Erases the sequence of characters in the range [first,last).
	// This effectively reduces the container size by the number of elements removed.
	// Relocates all the characters after the segment erased to their new positions.
	// Returns a pointer referring to the character that now occupies the position of the first character erased,
	// or string::end if no such character exists.

	//check last and first are reasonable, if not reset last and first
	if (first < this->sPtr || first >= this->sPtr + this->getSize())
		first = this->sPtr;

	if (last < this->sPtr || last >= this->sPtr + this->getSize())
		last = this->sPtr + this->getSize() - 1;


	//move character to erase
	/*
	use memcpy is more efficiently than memmove, but is not safe on follow case:
	index    0 1 2 3 4 5 6 7 8 9 10
	sPtr = [ a b c d e f g h i j k ]
	|	   |
	pos  pos+len
	memcpy may lead data damage

	*/

	memmove(first, last, last - first + 1);

	//reset size
	this->size -= last - first + 1;


	return first;
}

unsigned int String::find(char c, unsigned int pos) const
{
	// Searches the string for the first occurrence of the character specified by its arguments.
	// Returns the position of the first match. If no matches were found, the function returns string::npos.

	unsigned int length = this->getSize();
	if (pos >= length)
		return this->npos;
	for (size_t i = pos; i < length; i++)
	{
		if (this->sPtr[i] == c)
			return i;
	}

	return this->npos;

}

String String::substr(unsigned int pos, unsigned int len) const
{
	// Returns a newly constructed string object with its value initialized to a copy of a substring of this object.
	// The substring is the portion of the object that starts at character position pos and spans len characters
	// (or until the end of the string, whichever comes first).

	//check len is reasonable
	
	char *ptr;

	if (len <= size - pos)
	{
		ptr = new char[len + 1];
		memcpy(ptr, sPtr + pos, len);
		ptr[len + 1] = '\0';
		return *(new String(ptr, len + 1));
	} 
	else
	{
		ptr = new char[size - pos + 1];
		memcpy(ptr, sPtr + pos, size - pos);
		ptr[size - pos + 1] = '\0';
		return *(new String(ptr, size - pos + 1));
	}

}
